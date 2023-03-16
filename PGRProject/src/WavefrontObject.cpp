#include "WavefrontObject.h"

void WavefrontObject::AddVertex(float x, float y, float z) {
	m_Vertices.push_back(new Vertex(x, y, z));
}

void WavefrontObject::AddNormal(float x, float y, float z) {
	m_Normals.push_back(new Normal(x, y, z));
}

void WavefrontObject::AddTexCoords(float u, float v) {
	m_TexCoords.push_back(new TexCoords(u, v));
}

void WavefrontObject::AddFace(int v1, int v2, int v3) {
	m_Faces.push_back(new Face(m_Faces.size() + 1, v1, v2, v3, state_SmoothShading));
}
