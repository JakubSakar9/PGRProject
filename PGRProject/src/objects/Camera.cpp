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
	glm::vec4 upH = glm::toMat4(m_rotation) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec3 up = glm::vec3(upH) / upH.w;
	glm::vec4 forwardH = glm::toMat4(m_rotation) * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	glm::vec3 forward = glm::vec3(forwardH) / forwardH.w;
	return glm::lookAt(pos, forward + pos, up);
}

glm::mat4 Camera::ComputeSkyboxViewMatrix() {
	glm::vec3 up = m_rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(glm::vec3(0.0f), forward, up);
}

bool Camera::GenObjects() {
	m_aspectRatio = glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
	return ObjectInstance::GenObjects();
}

void Camera::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
	if (m_cameraId == ShaderProgram::ActiveCameraId()) {
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
				glm::vec3 pos = glm::vec3(m_globalModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
				program->SetUniform("cameraPosition", pos);
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
