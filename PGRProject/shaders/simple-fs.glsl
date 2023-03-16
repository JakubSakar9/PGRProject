#version 140
out vec4 fragmentColor;

in vec2 texCoords_v;

uniform mat4  u_PVM;   // transformation matrix
uniform sampler2D u_texDiffuse;

void main()
{
	vec4 diffuseColor = texture(u_texDiffuse, texCoords_v);
	if (diffuseColor.a < 0.1)
		discard;
	fragmentColor = diffuseColor;
}
