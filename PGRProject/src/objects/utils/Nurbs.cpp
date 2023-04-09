#include "Nurbs.h"

Nurbs::Nurbs(std::vector<glm::vec3> controlPoints) {
	m_controlPoints = controlPoints;
}

glm::vec3 Nurbs::CalculatePoint(float t) {
	return glm::vec3();
}
