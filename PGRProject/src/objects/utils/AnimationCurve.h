#pragma once

#include <iostream>

#include <cmath>

#include "pgr.h"

class AnimationCurve {
protected:
	float m_period;
public:
	virtual glm::vec3 SamplePosition(float t) = 0;
	virtual glm::quat SampleRotation(float t) = 0;
};