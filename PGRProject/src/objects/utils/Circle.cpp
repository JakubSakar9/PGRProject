#include "Circle.h"

glm::vec3 Circle::SamplePosition(float t) {
	float x = m_radius * glm::cos(2 * glm::pi<float>() * t / m_period);
	float z = m_radius * glm::sin(2 * glm::pi<float>() * t / m_period);
	return glm::vec3(x, 0.0f, z);
}

glm::quat Circle::SampleRotation(float t) {
	float param = remainder(t, m_period) / m_period;
	return glm::quat(glm::vec3(0.0f, -2 * param * glm::pi<float>(), 0.0f));
}
