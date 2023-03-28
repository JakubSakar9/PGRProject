#include "Rupee.h"

Rupee::Rupee() {
	m_Shader_type = SHADER_TYPE_DEFAULT;
	size_t lenVertices = sizeof(rupeeVertices);
	size_t lenIndices = sizeof(rupeeIndices);
	std::copy(rupeeVertices, rupeeVertices + lenVertices, std::back_inserter(m_Geometry.verticesData));
	std::copy(rupeeIndices, rupeeIndices + lenIndices, std::back_inserter(m_Geometry.indices));
	m_Geometry.numTriangles = 32;
	m_Geometry.numVertices = 96;
	m_Geometry.numAttributes = lenVertices / sizeof(float);
	m_Geometry.numAttributesPerVertex = VERTEX_SIZE;
	m_Geometry.numVertices = m_Geometry.numAttributes / m_Geometry.numAttributesPerVertex;

	m_Material = new Material("rupeeMaterial");
	m_Material->Diffuse(1.0f, 0.0f, 0.0f);
	m_Material->DiffuseMap("NONE");
	m_Material->Specular(1.0f, 0.2f, 0.2f);
	m_Material->SpecularExponent(10.0f);
	m_Scale = glm::vec3(1.0f);
	m_Position = glm::vec3(0.0f, 10.0f, 345.0f);
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
