#version 140

uniform mat4  u_pvMatrix;   // transformation matrix

in vec3 position;

out vec3 texCoords_v;

void main()
{
	vec4 pos = u_pvMatrix * vec4(position, 1.0f);
	gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
	texCoords_v = vec3(position.x, position.y, -position.z);
}
