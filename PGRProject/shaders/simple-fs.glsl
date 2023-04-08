#version 140
const int c_maxPointLights = 4;
const int c_maxSpotlights = 2;

out vec4 fragmentColor;

in vec3 position_v;
in vec2 texCoords_v;
in vec3 normal_v;

uniform mat4  u_pvmMatrix;   // transformation matrix
uniform vec3 u_cameraPosition;

struct AmbientLight {
	vec3 color;
	float intensity;
};


struct DirectionalLight {
	vec3 color;
	vec3 direction;
	float intensity;
};

struct PointLight {
	vec3 color;
	vec3 position;
	vec3 attenuation;
	float intensity;
};

struct Spotlight {
	vec3 color;
	vec3 position;
	vec3 attenuation;
	float intensity;
	vec3 direction;
	float size;
};

uniform vec3 u_colDiffuse;
uniform sampler2D u_texDiffuse;
uniform int u_useTexDiffuse;

uniform vec3 u_colSpecular;
uniform float u_specularExponent;

uniform float u_dissolveFactor;

uniform AmbientLight u_ambientLight;
uniform DirectionalLight u_directionalLight;
uniform PointLight u_pointLights[c_maxPointLights];
uniform Spotlight u_spotlights[c_maxSpotlights];

vec3 computeDiffuse(vec3 pointLightContributions[c_maxPointLights], vec3 pointLightDirections[c_maxPointLights],
					vec3 spotlightContributions[c_maxSpotlights], vec3 spotlightDirections[c_maxSpotlights], vec3 normal) {
	vec3 result = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < c_maxPointLights; i++) {
		float diffuseFactor = dot(normal, -pointLightDirections[i]);
		result += diffuseFactor * pointLightContributions[i];
	}
	for (int i = 0; i < c_maxSpotlights; i++) {
		float diffuseFactor = dot(normal, -spotlightDirections[i]);
		result += diffuseFactor * spotlightContributions[i];
	}
	float diffuseFactor = dot(normal, -normalize(u_directionalLight.direction));
	result += diffuseFactor * u_directionalLight.intensity * u_directionalLight.color;
	result *= u_colDiffuse;
	return clamp(result, 0.0f, 1.0f);
}

vec3 computeSpecular(vec3 pointLightContributions[c_maxPointLights], vec3 pointLightDirections[c_maxPointLights],
					vec3 spotlightContributions[c_maxSpotlights], vec3 spotlightDirections[c_maxSpotlights], vec3 normal) {
	vec3 result = vec3(0.0f, 0.0f, 0.0f);
	vec3 view = normalize(u_cameraPosition - position_v);
	for (int i = 0; i < c_maxPointLights; i++) {
		vec3 reflection = reflect(pointLightDirections[i], normal);
		float specularFactor = dot(view, reflection);
		result += specularFactor * pointLightContributions[i];
	}
	for (int i = 0; i < c_maxSpotlights; i++) {
		vec3 reflection = reflect(spotlightDirections[i], normal);
		float specularFactor = dot(view, reflection);
		result += specularFactor * spotlightContributions[i];
	}
	vec3 reflection = normalize(reflect(u_directionalLight.direction, normal_v));
	float specularFactor = dot(view, reflection);
	result += specularFactor * u_directionalLight.intensity * u_directionalLight.color;
	result *= u_colSpecular;
	return clamp(result, 0.0f, 1.0f);
}

void main()
{
	vec4 albedo;
	if (u_useTexDiffuse > 0) {
		albedo = texture(u_texDiffuse, texCoords_v);
	}
	else {
		albedo = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (albedo.a < 0.1) {
		discard;
	}

	// Computing several light properties ahead of time
	vec3 pointLightDirections[c_maxPointLights];
	vec3 pointLightContributions[c_maxPointLights];
	for (int i = 0; i < c_maxPointLights; i++) {
		PointLight curLight = u_pointLights[i];
		vec3 lightVector = curLight.position - position_v;
		pointLightDirections[i] = -normalize(lightVector);
		float d = length(lightVector);
		float attenuation = curLight.attenuation.z * pow(d, 2) + curLight.attenuation.y * d + curLight.attenuation.x;
		pointLightContributions[i] = curLight.color * curLight.intensity / attenuation;
	}

	vec3 spotlightDirections[c_maxSpotlights];
	vec3 spotlightContributions[c_maxSpotlights];
	for (int i = 0; i < c_maxSpotlights; i++) {
		Spotlight curLight = u_spotlights[i];
		vec3 lightVector = curLight.position - position_v;
		spotlightDirections[i] = -normalize(lightVector);
		float anglec = dot(normalize(curLight.direction), spotlightDirections[i]);
		if (anglec < cos(curLight.size)) {
			spotlightContributions[i] = vec3(0.0f, 0.0f, 0.0f);
			continue;
		}
		float d = length(lightVector);
		float attenuation = curLight.attenuation.z * pow(d, 2) + curLight.attenuation.y * d + curLight.attenuation.x;
		spotlightContributions[i] = curLight.color * curLight.intensity / attenuation;
	}

	float diffuseFactor = dot(normalize(normal_v), -normalize(u_directionalLight.direction));

	vec3 ambientComponent = u_ambientLight.color * u_ambientLight.intensity;
	vec3 diffuseComponent = computeDiffuse(pointLightContributions, pointLightDirections, spotlightContributions, spotlightDirections, normalize(normal_v));
	vec3 specularComponent = computeSpecular(pointLightContributions, pointLightDirections, spotlightContributions, spotlightDirections, normalize(normal_v));
	vec4 tempColor = albedo * vec4((ambientComponent + diffuseComponent + specularComponent), 1 - u_dissolveFactor);
	
	float d = length(position_v - u_cameraPosition);
	float disparity = 1.0f / (1.0f + d);
	float fogFactor = clamp(exp2(-disparity * 10.0f), 0.0f, 0.5f);
	fogFactor /= (1.0f + position_v.y * 0.2f);
	vec3 fogColor = vec3(0.4f);
	
	fragmentColor = (1 - fogFactor) * tempColor + fogFactor * vec4(fogColor, 1.0f);
}
