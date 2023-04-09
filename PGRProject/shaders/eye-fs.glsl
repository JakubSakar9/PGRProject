#version 140
out vec4 fragmentColor;

in vec3 position_v;
in vec2 texCoords_v;

uniform sampler2D u_texDiffuse;

uniform int u_frameId;
uniform int u_numFrames;

void main()
{
	vec4 albedo;
	vec2 texAnim = vec2((texCoords_v.x + u_frameId) / u_numFrames, texCoords_v.y);
	albedo = texture(u_texDiffuse, texAnim);
	if (albedo.a < 0.1) {
		discard;
	}
	fragmentColor = albedo;
}
