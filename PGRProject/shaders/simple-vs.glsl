#version 140

uniform mat4  u_PVM;   // transformation matrix

in vec3 position;
in vec3 normal;
in vec2 texCoords;

out vec3 position_v;
out vec3 normal_v;
out vec2 texCoords_v;

void main()
{
	gl_Position = u_PVM * vec4(position, 1.0f);
	position_v = position;
	texCoords_v = texCoords;
	normal_v = normal;
}
