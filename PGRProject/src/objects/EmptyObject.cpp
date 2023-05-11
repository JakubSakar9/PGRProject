#include "EmptyObject.h"

glm::mat4 EmptyObject::ComputeModelMatrix(float time)
{
	glm::vec3 effectivePosition = m_position;
	glm::quat effectiveRotation = m_rotation;

	if (m_curve) {
		effectivePosition += m_curve->SamplePosition(time);
		effectiveRotation = m_rotation * m_curve->SampleRotation(time);
	}

	glm::mat4 scaleMat = glm::scale(glm::mat4(), m_scale);
	glm::mat4 rotMat = glm::toMat4(effectiveRotation);
	glm::mat4 trMat = glm::translate(glm::mat4(), effectivePosition);
	return trMat * rotMat * scaleMat;
}

EmptyObject::EmptyObject(nlohmann::json source) {
	using json = nlohmann::json;
	InitTransform(source);
	InitChildren(source);

	if (source.contains("circle")) {
		json j_circle = source["circle"];
		m_curve = new Circle(j_circle["radius"], j_circle["period"]);
	}

	m_time = 0.0f;
}

void EmptyObject::InitChildren(nlohmann::json source) {
	using json = nlohmann::json;
	for (json c : source["children"]) {
		if (c["type"] == "static") {
			m_children.push_back(new StaticObject(c));
		}
		else if (c["type"] == "empty") {
			m_children.push_back(new EmptyObject(c));
		}
		else if (c["type"] == "eye") {
			m_children.push_back(new EyeObject(c));
		}
		else if (c["type"] == "water") {
			m_children.push_back(new Water(c));
		}
		else if (c["type"] == "rupee") {
			m_children.push_back(new Rupee(c));
		}
		else if (c["type"] == "pointLight") {
			PointLight* pl = new PointLight(c);
			m_children.push_back(pl);
		}
		else if (c["type"] == "spotlight") {
			Spotlight* sl = new Spotlight(c);
			m_children.push_back(sl);
		}
		else if (c["type"] == "camera") {
			Camera* cam = new Camera(c);
			m_children.push_back(cam);
		}
		else {
			std::cerr << "Invalid object type" << std::endl;
		}
	}
}

void EmptyObject::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	m_time += deltaTime;
	m_localModelMatrix = ComputeModelMatrix(m_time);

	m_globalRotation = parentRotation * m_rotation;
	if (m_curve) {
		m_globalRotation = m_globalRotation * m_curve->SampleRotation(m_time);
	}

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

void EmptyObject::ShowProperties() {
	ObjectInstance::ShowProperties();

	if (m_curve) {
		m_curve->ShowProperties();
	}
}
