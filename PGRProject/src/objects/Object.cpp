#include "Object.h"
#include <iostream>

void ObjectInstance::Update(float deltaTime, const glm::mat4* parentModelMatrix, glm::vec3 cameraPos) {
	m_localModelMatrix = ComputeModelMatrix();

	// if we have parent, multiply parent's matrix with ours
	if (parentModelMatrix != nullptr)
		m_globalModelMatrix = *parentModelMatrix * m_localModelMatrix;
	else
		m_globalModelMatrix = m_localModelMatrix;
	
	for (auto child : children) {
		if (child != nullptr)
			child->Update(deltaTime, &m_globalModelMatrix, cameraPos);
	}
}

void ObjectInstance::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram *shaderProgram) {
	// process all children
	for (auto child : children) {
		if (child != nullptr)
			child->Draw(viewMatrix, projectionMatrix, shaderProgram);
	}
}

bool ObjectInstance::GenObjects(ShaderProgram *shaderProgram) {
	for (auto child : children) {
		if (child != nullptr)
			child->GenObjects(shaderProgram);
	}
	return true;
}

void ObjectInstance::Translate(glm::vec3 delta) {
	m_position += delta;
}

void ObjectInstance::Scale(glm::vec3 scale) {
	m_scale *= scale;
}

void ObjectInstance::AddCollider(glm::vec3& size) {
	m_collider = new BoxCollider(size);
}

void ObjectInstance::UpdateColliders(std::vector<BoxCollider *>& colliders) {
	if (m_collider) {
		colliders.push_back(m_collider->Scale(m_globalModelMatrix));
	}
}
glm::mat4 ObjectInstance::ComputeModelMatrix()
{
	glm::mat4 modelMat = glm::scale(glm::mat4(), m_scale);
	modelMat = glm::toMat4(m_rotation) * modelMat;
	modelMat = glm::translate(modelMat, m_position);
	return modelMat;
}
