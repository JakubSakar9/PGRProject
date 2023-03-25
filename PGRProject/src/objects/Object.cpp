#include "Object.h"
#include <iostream>

void ObjectInstance::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	m_LocalModelMatrix = ComputeModelMatrix();

	// if we have parent, multiply parent's matrix with ours
	if (parentModelMatrix != nullptr)
		m_Global_model_matrix = *parentModelMatrix * m_LocalModelMatrix;
	else
		m_Global_model_matrix = m_LocalModelMatrix;
	
	for (auto child : children) {
		if (child != nullptr)
			child->Update(deltaTime, &m_Global_model_matrix);
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
	m_Position += delta;
}

glm::mat4 ObjectInstance::ComputeModelMatrix()
{
	glm::mat4 modelMat = glm::scale(glm::mat4(), m_Scale);
	modelMat = glm::toMat4(m_Rotation) * modelMat;
	modelMat = glm::translate(modelMat, m_Position);
	return modelMat;
}
