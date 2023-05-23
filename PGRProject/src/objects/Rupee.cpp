//----------------------------------------------------------------------------------------
/**
 * \file       Rupee.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "Rupee.h"

int Rupee::s_numRupees = 1;

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

	m_rupeeId = s_numRupees++;
}

void Rupee::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	if (InputManager::Get().ReadStencils() == m_rupeeId) {
		m_spinning = true;
	}
	else {
		m_spinning = false;
	}

	if (m_spinning) {
		glm::quat rupeeRotation = glm::quat(glm::vec3(0.0f, 0.1f * deltaTime, 0.0f));
		m_rotation = rupeeRotation * m_rotation;
	}
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
}

void Rupee::ShowProperties() {
	ObjectInstance::ShowProperties();
}

void Rupee::Draw() {
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_ZERO, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, m_rupeeId, 0xFF);
	StaticObject::Draw();
	glDisable(GL_STENCIL_TEST);
}

bool Rupee::GenObjects(std::vector<ObjectInstance *>& transparentObjects) {
	m_transparent = true;
	transparentObjects.push_back(this);
	return StaticObject::GenObjects(transparentObjects);
}
