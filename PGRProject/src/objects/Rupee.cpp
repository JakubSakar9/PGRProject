#include "Rupee.h"

Rupee::Rupee(nlohmann::json source) {
	InitTransform(source);

	size_t lenVertices = sizeof(rupeeVertices);
	size_t lenIndices = sizeof(rupeeIndices);
	std::copy(rupeeVertices, rupeeVertices + lenVertices, std::back_inserter(m_geometry.verticesData));
	std::copy(rupeeIndices, rupeeIndices + lenIndices, std::back_inserter(m_geometry.indices));
	
	m_geometry.numTriangles = 32;
	m_geometry.numVertices = 96;
	m_geometry.numAttributes = lenVertices / sizeof(float);
	m_geometry.numAttributesPerVertex = VERTEX_SIZE;
	m_geometry.numVertices = m_geometry.numAttributes / m_geometry.numAttributesPerVertex;

	m_material = ResourceManager::Get().GetMaterial(source["material"]);
}

void Rupee::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	StaticObject::Update(deltaTime, parentModelMatrix);
}

void Rupee::Draw() {
	StaticObject::Draw();
}

bool Rupee::GenObjects() {
	return StaticObject::GenObjects();
}
