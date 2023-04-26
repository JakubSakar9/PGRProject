#version 140

uniform mat4  u_pvMatrix;   // transformation matrix
uniform mat4  u_mMatrix;   // transformation matrix

in vec3 position;
in vec3 normal;
in vec2 texCoords;

out vec3 position_v;
out vec3 normal_v;
out vec2 texCoords_v;

void main()
{
	vec4 tmpPosition = u_mMatrix * vec4(position, 1.0f);
	gl_Position = u_pvMatrix * tmpPosition;
	position_v = vec3(tmpPosition.x, tmpPosition.y, tmpPosition.z);
	texCoords_v = texCoords;
	normal_v = normal;
}
