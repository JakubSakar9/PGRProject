#version 140

out vec4 fragmentColor;

in vec3 texCoords_v;

uniform samplerCube u_skybox;

void main() {
	vec4 tmpColor = texture(u_skybox, texCoords_v);
	float fogFactor = clamp(exp2(-texCoords_v.y * 10.0f), 0.0f, 1.0f);
	fragmentColor = (1 - fogFactor) * tmpColor + fogFactor * vec4(vec3(0.4f), 1.0f);
}