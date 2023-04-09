#pragma once

#include "pgr.h"

class Nurbs
{
private:
	std::vector<glm::vec3> m_controlPoints;
	std::vector<float> m_knotVector;
public:
	Nurbs() {}
	Nurbs(std::vector<glm::vec3> controlPoints);

	glm::vec3 CalculatePoint(float t);
};

