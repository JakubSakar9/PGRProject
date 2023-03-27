#include "Camera.h"

glm::mat4 Camera::ComputeViewMatrix()
{
	glm::vec3 up = m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::lookAt(m_Position, forward + m_Position, up);
}

bool Camera::Init()
{
	m_AspectRatio = glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
	return true;
}

void Camera::Update(ShaderProgram* shaderProgram, float deltaTime)
{
	glm::vec3 velocity = InputManager::Get().RelativeVelocity() * m_MovementSpeed;
	glm::vec3 deltaPosition = m_Rotation * velocity;
	m_Rotation = InputManager::Get().CalculateRotation();
	m_Position += deltaPosition;
}
