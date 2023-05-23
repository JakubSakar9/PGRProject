//----------------------------------------------------------------------------------------
/**
 * \file       Object.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "Object.h"
#include <iostream>

void ObjectInstance::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	m_localModelMatrix = ComputeModelMatrix();

	m_globalRotation = parentRotation * m_rotation;

	m_globalPosition = glm::vec3(m_globalModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));


	// if we have parent, multiply parent's matrix with ours
	if (parentModelMatrix != nullptr)
		m_globalModelMatrix = *parentModelMatrix * m_localModelMatrix;
	else
		m_globalModelMatrix = m_localModelMatrix;
	
	for (auto child : m_children) {
		if (child != nullptr)
			child->Update(deltaTime, &m_globalModelMatrix, m_globalRotation);
	}
}

void ObjectInstance::Draw() {
	// process all children
	for (auto child : m_children) {
		if (child != nullptr && !child->m_transparent)
			child->Draw();
	}
}

bool ObjectInstance::GenObjects(std::vector<ObjectInstance*>& transparentObjects) {
	for (auto child : m_children) {
		if (child != nullptr)
			child->GenObjects(transparentObjects);
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

void ObjectInstance::RenderGraph() {
	if (m_children.size() == 0) {
		ImGui::Text(m_name.c_str());
		if (ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing()) {
			m_clicked = true;
		}
		return;
	}
	if (ImGui::TreeNode(m_name.c_str()) ) {
		if (ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing()) {
			m_clicked = true;
		}
		for (auto* child : m_children) {
			child->RenderGraph();
		}
		ImGui::TreePop();
	}
}

ObjectInstance* ObjectInstance::SelectObject() {
	ObjectInstance* ret = nullptr;
	if (m_clicked) {
		m_clicked = false;
		ret = this;
	}
	auto it = m_children.begin();
	while (!ret) {
		if (it == m_children.end())
			break;
		ret = (*it)->SelectObject();
		it++;
	}
	return ret;
}

void ObjectInstance::ShowProperties() {
	ImGui::Text((std::string("Name: ") + m_name).c_str());
	float position[3] = { m_position.x, m_position.y, m_position.z };
	ImGui::InputFloat3("Position", position);
	m_position = glm::vec3(position[0], position[1], position[2]);
	
	float rotation[4] = { m_rotation.w, m_rotation.x, m_rotation.y, m_rotation.z };
	ImGui::InputFloat4("Rotation", rotation);
	m_rotation = glm::quat(rotation[0], rotation[1], rotation[2], rotation[3]);

	float scale[3] = { m_scale.x, m_scale.y, m_scale.z };
	ImGui::InputFloat3("Scale", scale);
	m_scale = glm::vec3(scale[0], scale[1], scale[2]);
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
	float angleX = glm::radians((float)j_rotation[0]);
	float angleY = glm::radians((float)j_rotation[1]);
	float angleZ = glm::radians((float)j_rotation[2]);
	m_rotation = glm::quat(glm::vec3(angleX, angleY, angleZ));
	json j_scale = source["scale"];
	m_scale = glm::vec3(j_scale[0], j_scale[1], j_scale[2]);

	if (source.contains("collider")) {
		json j_collider = source["collider"];
		m_collider = new BoxCollider(glm::vec3(j_collider[0], j_collider[1], j_collider[2]));
	}
}
