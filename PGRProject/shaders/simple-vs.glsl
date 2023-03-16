#version 140
in vec3 position;

uniform mat4  u_PVM;   // transformation matrix

in vec2 texCoords;

out vec2 texCoords_v;

void main()
{
	gl_Position = u_PVM * vec4(position, 1.0f);
	texCoords_v = texCoords;
}
