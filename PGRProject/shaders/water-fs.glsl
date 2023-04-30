#version 140

const float c_pi = 3.14159265;
const int c_maxPointLights = 10;
const int c_maxSpotlights = 2;

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


uniform vec3 u_cameraPosition;

uniform vec3 u_colAlbedo;

uniform vec3 u_colEmission;

uniform float u_specular;

uniform float u_roughness;

uniform float u_transmission;

uniform sampler2D u_texNormal1;
uniform sampler2D u_texNormal2;

uniform int u_numPointLights;
uniform int u_numSpotlights;

uniform float u_time;
uniform float u_waveSpeed;

uniform AmbientLight u_ambientLight;
uniform DirectionalLight u_directionalLight;
uniform PointLight u_pointLights[c_maxPointLights];
uniform Spotlight u_spotlights[c_maxSpotlights];

in vec3 position_v;

out vec4 fragmentColor;

vec3 V = normalize(u_cameraPosition - position_v);
float A = u_roughness * u_roughness;

// Safe dot product
inline float dotS(vec3 a, vec3 b) {
	return max(dot(a, b), 0.0f);
}

// Safe inverse (only works for positive denominator)
float invS(float a) {
	float eps = 0.000001;
	return 1.0f / max(a, eps);
}

vec3 sRGBtoLinear(vec3 color) {
    return pow(color, vec3(2.2));
}


vec3 linearTosRGB(vec3 color) {
    return pow(color, vec3(1.0 / 2.2));
}

float fresnelFn(vec3 H) {
	return u_specular + (1 - u_specular) * pow((1 - dotS(V, H)), 5.0f);
}

// Computed using lambertian model
vec3 fDiffuse() {
	vec3 colAlbedo = sRGBtoLinear(u_colAlbedo);
	return colAlbedo / c_pi;
}

// GGX Trowbridge-Reitz
float distributionFn(vec3 H, vec3 N) {
	float A2 = A * A;
	float tmp = dotS(N, H) * dotS(N, H) * (A2 - 1) + 1;
	float denom = tmp * tmp;
	return A2 * invS(denom) / c_pi;
}

float geometryComponent(vec3 X, vec3 N) {
	float num = dotS(N, X);
	float k = A * 0.5f;
	float denom = dotS(N, X) * (1 - k) + k;
	return num * invS(denom);
}

float geometryFn(vec3 L, vec3 N) {
	return geometryComponent(L, N) * geometryComponent(V, N);
}

// Computed using Cook-Torrance equation
vec3 fSpecular(vec3 H, vec3 L, vec3 N) {
	float num = distributionFn(H, N) * geometryFn(L, N);
	float denom = 4.0f * dotS(V, N) * dotS(L, N);
	float result = num * invS(denom);
	return vec3(max(result, 0.0f));
}

vec3 BRDFColor(vec3 H, vec3 L, vec3 N) {
	float ks = fresnelFn(H);
	float kd = 1 - ks;
	return fDiffuse() * kd + fSpecular(H, L, N);
}

float BRDFAlpha(vec3 H) {
	float ks = fresnelFn(H);
	float kd = 1 - ks;
	float alpha = ks + kd * (1- u_transmission);
	return alpha;
}

vec3 computeDirectionalColor(vec3 N) {
	vec3 L = normalize(-u_directionalLight.direction);
	vec3 H = normalize(V + L);
	vec3 result = BRDFColor(H, L, N) * dotS(L, N) * sRGBtoLinear(u_directionalLight.color) * u_directionalLight.intensity;
	return max(result, 0);
}

vec3 computePointLightColor(vec3 N) {
	vec3 result = vec3(0.0f);
	for (int i = 0; i < u_numPointLights; i++) {
		PointLight pl = u_pointLights[i];
		vec3 lightVector = pl.position - position_v;
		float D = length(lightVector);
		vec3 L = normalize(lightVector);
		vec3 H = normalize(V + L);
		float attenuation = pl.attenuation.z * D * D + pl.attenuation.y * D + pl.attenuation.x;
		float intensity = pl.intensity / attenuation;
		result += BRDFColor(H, L, N) * dotS(L, N) * sRGBtoLinear(pl.color) * intensity;
	}
	return max(result, vec3(0.0f));
}

vec3 computeSpotlightColor(vec3 N) {
	vec3 result = vec3(0.0f);
	for (int i = 0; i < u_numSpotlights; i++) {
		Spotlight sl = u_spotlights[i];
		vec3 lightVector = sl.position - position_v;
		float D = 
		length(lightVector);
		vec3 L = normalize(lightVector);
		float anglec = dot(normalize(-sl.direction), L);
		if (anglec < cos(sl.size)) {
			continue;
		}
		vec3 H = normalize(V + L);
		float attenuation = sl.attenuation.z * D * D + sl.attenuation.y * D + sl.attenuation.x;
		float intensity = sl.intensity / attenuation;
		result += BRDFColor(H, L, N) * dotS(L, N) * sRGBtoLinear(sl.color) * intensity;
	}
	return clamp(result, vec3(0), vec3(1));
}

vec3 sampleNormalMaps() {
	float delta = u_time * u_waveSpeed * 0.01;
	vec2 uv1 = vec2(position_v.x + delta, position_v.z + delta) * 0.1;
	vec2 uv2 = vec2(position_v.x - delta, position_v.z - delta) * 0.1;
	vec3 tex1 = vec3(texture(u_texNormal1, uv1));
	vec3 tex2 = vec3(texture(u_texNormal2, uv2));
	return tex1 + tex2 - vec3(0.5f, 0.5f, 1.0f);
}

void main() {
	vec3 finalColor = sRGBtoLinear(u_colEmission);

	vec3 N = sampleNormalMaps() * 2 - 1;
	N = normalize(vec3(N.x, N.z, N.y));

	finalColor += computeDirectionalColor(N);
	finalColor += computePointLightColor(N);
	finalColor += computeSpotlightColor(N);

	vec3 ambientComponent = u_ambientLight.color * u_ambientLight.intensity * u_colAlbedo;
	finalColor += ambientComponent;

	fragmentColor = vec4(finalColor, 1.0f);

	// Fog computation
	vec4 fogColor = vec4(0.3f, 0.3f, 0.3f, 1.0f);
	float d = length(position_v - u_cameraPosition);
	float fogFactor = clamp(1 - exp2(-d * 0.01f), 0.0f, 1.0f);
	fogFactor *= exp(-(position_v.y + 0.5) * 0.5f);
	fragmentColor = fogFactor * fogColor + (1 - fogFactor) * fragmentColor;
}