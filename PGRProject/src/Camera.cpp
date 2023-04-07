#include "Camera.h"

glm::mat4 Camera::ComputeViewMatrix()
{
	glm::vec3 up = m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(m_Position, forward + m_Position, up);
}

glm::mat4 Camera::ComputeSkyboxViewMatrix()
{
	glm::vec3 up = m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(glm::vec3(0.0f), forward, up);
}

bool Camera::Init()
{
	m_AspectRatio = glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
	return true;
}

void Camera::Update(ShaderProgram* shaderProgram, float deltaTime)
{
	if (m_dynamic) {
		std::cout << m_Position.x << " " << m_Position.y << " " << m_Position.z << std::endl;;
		glm::vec3 velocity = InputManager::Get().RelativeVelocity() * m_MovementSpeed;
		glm::vec3 deltaPosition = m_Rotation * velocity;
		m_Rotation = InputManager::Get().CalculateRotation();
		m_Position += deltaPosition;
		
		m_Position.x = (m_Position.x < m_lBound.x) ? m_lBound.x : m_Position.x;
		m_Position.y = (m_Position.y < m_lBound.y) ? m_lBound.y : m_Position.y;
		m_Position.z = (m_Position.z < m_lBound.z) ? m_lBound.z : m_Position.z;

		m_Position.x = (m_Position.x > m_uBound.x) ? m_uBound.x : m_Position.x;
		m_Position.y = (m_Position.y > m_uBound.y) ? m_uBound.y : m_Position.y;
		m_Position.z = (m_Position.z > m_uBound.z) ? m_uBound.z : m_Position.z;
	}
	ShaderProgram::s_cameraPosition = m_Position;
}

void Camera::ChangeBounds(glm::vec3 lBound, glm::vec3 uBound) {
	m_lBound = lBound;
	m_uBound = uBound;
}
