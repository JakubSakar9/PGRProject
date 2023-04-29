#include "Rupee.h"

int Rupee::s_rupeeId = 1;

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

	m_rupeeId = s_rupeeId++;
}

void Rupee::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	if (InputManager::Get().ReadStencils() == m_rupeeId) {
		m_rotating = true;
	}
	else {
		m_rotating = false;
	}

	if (m_rotating) {
		glm::quat rupeeRotation = glm::quat(glm::vec3(0.0f, 0.1f * deltaTime, 0.0f));
		m_rotation = rupeeRotation * m_rotation;
	}
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
}

void Rupee::Draw() {
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_ZERO, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, m_rupeeId, 0xFF);
	StaticObject::Draw();
	glDisable(GL_STENCIL_TEST);
}

bool Rupee::GenObjects() {
	return StaticObject::GenObjects();
}
