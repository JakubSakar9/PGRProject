//----------------------------------------------------------------------------------------
/**
 * \file       Camera.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "Camera.h"

std::vector<BoxCollider*> Camera::s_colliders;

Camera::Camera(nlohmann::json source) {
	InitTransform(source);

	using json = nlohmann::json;
	json j_bounds = source["bounds"];
	m_lBound = glm::vec3(j_bounds[0], j_bounds[1], j_bounds[2]);
	m_uBound = glm::vec3(j_bounds[3], j_bounds[4], j_bounds[5]);
	m_fovDegrees = source["fov"];
	json j_clipping = source["clipping"];
	m_nearPlane = j_clipping[0];
	m_farPlane = j_clipping[1];
	m_movementSpeed = source["movementSpeed"];
	m_dynamic = source["dynamic"];
	m_aspectRatio = 1.0f;

	if (m_dynamic) {
		m_cameraId = 0;
	}
	else {
		m_cameraId = ShaderProgram::AddCamera();
	}
}

glm::mat4 Camera::ComputeViewMatrix() {
	glm::vec4 posH = m_globalModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 pos = glm::vec3(posH) / posH.w;
	glm::vec3 up = m_globalRotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_globalRotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(pos, forward + pos, up);
}

glm::mat4 Camera::ComputeSkyboxViewMatrix() {
	glm::vec3 up = m_globalRotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_globalRotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(glm::vec3(0.0f), forward, up);
}

void Camera::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
	if (m_cameraId == ShaderProgram::ActiveCameraId()) {
		ShaderProgram::s_activeCameraPosition = m_globalPosition;
		for (int i = 0; i < SHADER_TYPE_N; i++) {
			ShaderProgram* program = ShaderProgram::GetShader((ShaderType)i);
			program->UseShader();
			glm::mat4 projection = ComputeProjectionMatrix();
			glm::mat4 pvMatrix;
			if ((ShaderType)i == SHADER_TYPE_SKYBOX) {
				glm::mat4 view = ComputeSkyboxViewMatrix();
				pvMatrix = projection * view;
			}
			else {
				glm::mat4 view = ComputeViewMatrix();
				pvMatrix = projection * view;
			}
			program->SetUniform("pvMatrix", pvMatrix);
			if ((ShaderType)i == SHADER_TYPE_DEFAULT || (ShaderType)i == SHADER_TYPE_WATER) {
				program->SetUniform("cameraPosition", m_globalPosition);
			}
		}
	}
	if (m_dynamic) {
		glm::vec3 prevPosition = m_position;
		glm::vec3 velocity = InputManager::Get().RelativeVelocity() * m_movementSpeed;
		glm::vec3 deltaPosition = m_rotation * velocity;
		m_rotation = InputManager::Get().CalculateRotation();
		m_position += deltaPosition;

		m_position.x = (m_position.x < m_lBound.x) ? m_lBound.x : m_position.x;
		m_position.y = (m_position.y < m_lBound.y) ? m_lBound.y : m_position.y;
		m_position.z = (m_position.z < m_lBound.z) ? m_lBound.z : m_position.z;

		m_position.x = (m_position.x > m_uBound.x) ? m_uBound.x : m_position.x;
		m_position.y = (m_position.y > m_uBound.y) ? m_uBound.y : m_position.y;
		m_position.z = (m_position.z > m_uBound.z) ? m_uBound.z : m_position.z;

		for (auto c : s_colliders) {
			glm::vec3 lBound = c->LBound();
			glm::vec3 uBound = c->UBound();

			if (m_position.x > lBound.x
				&& m_position.y > lBound.y
				&& m_position.z > lBound.z
				&& m_position.x < uBound.x
				&& m_position.y < uBound.y
				&& m_position.z < uBound.z) {
				m_position = prevPosition;
			}
		}
	}
}

void Camera::ChangeBounds(glm::vec3 lBound, glm::vec3 uBound) {
	m_lBound = lBound;
	m_uBound = uBound;
}

void Camera::UpdateColliders(std::vector<BoxCollider*> colliders) {
	for (BoxCollider* b : s_colliders) {
		delete b;
	}
	s_colliders.clear();
	s_colliders = colliders;
}

void Camera::ShowProperties() {
	ObjectInstance::ShowProperties();
	if (ImGui::CollapsingHeader("Camera Properties")) {
		ImGui::DragFloat("Near Plane", &m_nearPlane);
		ImGui::DragFloat("Far Plane", &m_farPlane);
		ImGui::DragFloat("FOV", &m_fovDegrees);
		ImGui::InputFloat("Aspect ratio", &m_aspectRatio);
		if (m_dynamic) {
			float lBound[3] = { m_lBound.x, m_lBound.y, m_lBound.z };
			ImGui::DragFloat3("Lower Bound", lBound);
			m_lBound = glm::vec3(lBound[0], lBound[1], lBound[2]);

			float uBound[3] = { m_uBound.x, m_uBound.y, m_uBound.z };
			ImGui::DragFloat3("Upper Bound", uBound);
			m_uBound = glm::vec3(uBound[0], uBound[1], uBound[2]);

			ImGui::DragFloat("Movement Speed", &m_movementSpeed);
		}
	}
}
