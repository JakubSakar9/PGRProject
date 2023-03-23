#version 140
out vec4 fragmentColor;

in vec2 texCoords_v;

uniform mat4  u_PVM;   // transformation matrix

uniform vec3 u_colDiffuse;
uniform sampler2D u_texDiffuse;
uniform int u_useTexDiffuse;

void main()
{
	vec4 diffuseColor;
	if (u_useTexDiffuse > 0) {
		diffuseColor = texture(u_texDiffuse, texCoords_v);
	}
	else {
		diffuseColor = vec4(u_colDiffuse, 1.0f);
	}
	if (diffuseColor.a < 0.1)
		discard;
	fragmentColor = diffuseColor;
}
