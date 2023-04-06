#version 140

out vec4 fragmentColor;

in vec3 texCoords_v;

uniform samplerCube u_skybox;

void main() {
	fragmentColor = texture(u_skybox, texCoords_v);
}