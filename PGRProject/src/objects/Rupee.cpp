#include "Rupee.h"

Rupee::Rupee() {
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
	m_material->Dissolve(0.4f, false);
	m_scale = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f, 10.0f, 345.0f);
}

Rupee::Rupee(nlohmann::json source) {
	InitTransform(source);
	InitChildren(source);

	size_t lenVertices = sizeof(rupeeVertices);
	size_t lenIndices = sizeof(rupeeIndices);
	std::copy(rupeeVertices, rupeeVertices + lenVertices, std::back_inserter(m_geometry.verticesData));
	std::copy(rupeeIndices, rupeeIndices + lenIndices, std::back_inserter(m_geometry.indices));
	
	m_geometry.numTriangles = 32;
	m_geometry.numVertices = 96;
	m_geometry.numAttributes = lenVertices / sizeof(float);
	m_geometry.numAttributesPerVertex = VERTEX_SIZE;
	m_geometry.numVertices = m_geometry.numAttributes / m_geometry.numAttributesPerVertex;


}

void Rupee::Update(float deltaTime, const glm::mat4* parentModelMatrix, glm::vec3 cameraPos) {
	StaticObject::Update(deltaTime, parentModelMatrix, cameraPos);
}

void Rupee::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	StaticObject::Draw(viewMatrix, projectionMatrix);
}

bool Rupee::GenObjects(ShaderType shaderType) {
	m_shaderType = shaderType;
	return StaticObject::GenObjects(shaderType);
}
