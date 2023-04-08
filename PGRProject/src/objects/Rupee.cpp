#include "Rupee.h"

Rupee::Rupee() {
	m_shaderType = SHADER_TYPE_DEFAULT;
	size_t lenVertices = sizeof(rupeeVertices);
	size_t lenIndices = sizeof(rupeeIndices);
	std::copy(rupeeVertices, rupeeVertices + lenVertices, std::back_inserter(m_geometry.verticesData));
	std::copy(rupeeIndices, rupeeIndices + lenIndices, std::back_inserter(m_geometry.indices));
	m_geometry.numTriangles = 32;
	m_geometry.numVertices = 96;
	m_geometry.numAttributes = lenVertices / sizeof(float);
	m_geometry.numAttributesPerVertex = VERTEX_SIZE;
	m_geometry.numVertices = m_geometry.numAttributes / m_geometry.numAttributesPerVertex;

	m_material = new Material("rupeeMaterial");
	m_material->Diffuse(1.0f, 0.0f, 0.0f);
	m_material->DiffuseMap("NONE");
	m_material->Specular(1.0f, 0.2f, 0.2f);
	m_material->SpecularExponent(10.0f);
	m_scale = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f, 10.0f, 345.0f);
}

void Rupee::Update(float deltaTime, const glm::mat4* parentModelMatrix, glm::vec3 cameraPos) {
	StaticObject::Update(deltaTime, parentModelMatrix, cameraPos);
}

void Rupee::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram* shaderProgram) {
	StaticObject::Draw(viewMatrix, projectionMatrix, shaderProgram);
}

bool Rupee::GenObjects(ShaderProgram* shaderProgram)
{
	return StaticObject::GenObjects(shaderProgram);
}
