#version 140
out vec4 fragmentColor;

in vec3 position_v;
in vec2 texCoords_v;
in vec3 normal_v;

uniform mat4  u_PVM;   // transformation matrix
uniform vec3 u_localCameraPosition;

struct AmbientLight {
	vec3 color;
	float intensity;
};


struct DirectionalLight {
	vec3 color;
	vec3 direction;
	float intensity;
};

uniform vec3 u_colDiffuse;
uniform sampler2D u_texDiffuse;
uniform int u_useTexDiffuse;

uniform vec3 u_colSpecular;
uniform float u_specularExponent;

uniform AmbientLight u_ambientLight;
uniform DirectionalLight u_directionalLight;

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

	vec3 ambientComponent = u_ambientLight.color * u_ambientLight.intensity;

	float diffuseIntensity = dot(normalize(normal_v), -normalize(u_directionalLight.direction)) * u_directionalLight.intensity;
	vec3 diffuseComponent = diffuseIntensity * u_directionalLight.color * u_colDiffuse;
	diffuseComponent = clamp(diffuseComponent, 0.0f, 1.0f);

	vec3 view = normalize(u_localCameraPosition - position_v);
	vec3 reflection = normalize(reflect(u_directionalLight.direction, normal_v));
	float specularIntensity = dot(view, reflection) * u_directionalLight.intensity;
	specularIntensity = pow(specularIntensity, u_specularExponent);
	vec3 specularComponent = u_colSpecular * specularIntensity * u_directionalLight.color;
	specularComponent = clamp(specularComponent, 0.0f, 1.0f);

	fragmentColor = albedo * vec4((ambientComponent + diffuseComponent + specularComponent), 1.0f);
}
