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

void ObjectInstance::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	// process all children
	for (auto child : children) {
		if (child != nullptr)
			child->Draw(viewMatrix, projectionMatrix);
	}
}

bool ObjectInstance::GenObjects(ShaderType shaderType) {
	m_shaderType = shaderType;
	for (auto child : children) {
		if (child != nullptr)
			child->GenObjects(shaderType);
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

void ObjectInstance::InitTransform(nlohmann::json source) {
	m_shaderType = SHADER_TYPE_DEFAULT;

	using json = nlohmann::json;
	m_name = std::string(source["name"]);
	json j_position = source["position"];
	m_position = glm::vec3(j_position[0], j_position[1], j_position[2]);
	json j_rotation = source["rotation"];
	glm::quat quatX = glm::quat(glm::radians(j_rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat quatY = glm::quat(glm::radians(j_rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat quatZ = glm::quat(glm::radians(j_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	m_rotation = quatX * quatY * quatZ;
	json j_scale = source["scale"];
	m_scale = glm::vec3(j_scale[0], j_scale[1], j_scale[2]);
}

void ObjectInstance::InitChildren(nlohmann::json source) {
	using json = nlohmann::json;

	for (json c : source["children"]) {
		if (source["type"] == "staticObject") {
			children.push_back(new StaticObject(c));
		}
		else if (source["type"] == "emptyObject") {
			children.push_back(new EmptyObject(c));
		}
		else if (source["type"] == "eye") {
			children.push_back(new EyeObject(c));
		}
		else if (source["type"] == "rupee") {
			children.push_back(new Rupee(c));
		}
		else if (source["type"] == "pointLight") {
			children.push_back(new PointLight(c));
		}
		else if (source["type"] == "spotlight") {
			children.push_back(new Spotlight(c));
		}
		else if (source["type"] == "camera") {
			children.push_back(new Camera(c));
		}
		else {
			std::cerr << "Invalid object type" << std::endl;
		}
	}
}
