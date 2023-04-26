#include "Object.h"
#include <iostream>

void ObjectInstance::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	m_localModelMatrix = ComputeModelMatrix();

	// if we have parent, multiply parent's matrix with ours
	if (parentModelMatrix != nullptr)
		m_globalModelMatrix = *parentModelMatrix * m_localModelMatrix;
	else
		m_globalModelMatrix = m_localModelMatrix;
	
	for (auto child : m_children) {
		if (child != nullptr)
			child->Update(deltaTime, &m_globalModelMatrix);
	}
}

void ObjectInstance::Draw() {
	// process all children
	for (auto child : m_children) {
		if (child != nullptr)
			child->Draw();
	}
}

bool ObjectInstance::GenObjects() {
	for (auto child : m_children) {
		if (child != nullptr)
			child->GenObjects();
	}
	return true;
}

void ObjectInstance::Translate(glm::vec3 delta) {
	m_position += delta;
}

void ObjectInstance::Scale(glm::vec3 scale) {
	m_scale *= scale;
}

void ObjectInstance::UpdateColliders(std::vector<BoxCollider *>& colliders) {
	if (m_collider) {
		colliders.push_back(m_collider->Scale(m_globalModelMatrix));
	}
	for (auto* child : m_children) {
		child->UpdateColliders(colliders);
	}
}

glm::mat4 ObjectInstance::ComputeModelMatrix()
{
	glm::mat4 scaleMat = glm::scale(glm::mat4(), m_scale);
	glm::mat4 rotMat = glm::toMat4(m_rotation);
	glm::mat4 trMat = glm::translate(glm::mat4(), m_position);
	return trMat * rotMat * scaleMat;
}

void ObjectInstance::InitTransform(nlohmann::json source) {
	m_shaderType = SHADER_TYPE_DEFAULT;

	using json = nlohmann::json;
	std::string nameTemp = source["name"];
	m_name = nameTemp;
	json j_position = source["position"];
	m_position = glm::vec3(j_position[0], j_position[1], j_position[2]);
	json j_rotation = source["rotation"];
	glm::quat quatX = glm::quat(glm::radians((float) j_rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat quatY = glm::quat(glm::radians((float) j_rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat quatZ = glm::quat(glm::radians((float) j_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	m_rotation = quatX * quatY * quatZ;
	json j_scale = source["scale"];
	m_scale = glm::vec3(j_scale[0], j_scale[1], j_scale[2]);

	if (source.contains("collider")) {
		json j_collider = source["collider"];
		m_collider = new BoxCollider(glm::vec3(j_collider[0], j_collider[1], j_collider[2]));
	}
}
