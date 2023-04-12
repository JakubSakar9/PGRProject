#include "Camera.h"

Camera::Camera(nlohmann::json source) {
	InitTransform(source);
	InitChildren(source);

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
}

glm::mat4 Camera::ComputeViewMatrix()
{
	glm::vec3 up = m_rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(m_position, forward + m_position, up);
}

glm::mat4 Camera::ComputeSkyboxViewMatrix()
{
	glm::vec3 up = m_rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(glm::vec3(0.0f), forward, up);
}

bool Camera::Init()
{
	m_aspectRatio = glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
	return true;
}

void Camera::Update(std::vector<BoxCollider*> colliders, float deltaTime) {
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

		for (auto c : colliders) {
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
	ShaderProgram::s_cameraPosition = m_position;
}

void Camera::ChangeBounds(glm::vec3 lBound, glm::vec3 uBound) {
	m_lBound = lBound;
	m_uBound = uBound;
}
