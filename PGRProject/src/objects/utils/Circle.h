#pragma once
#include "AnimationCurve.h"
class Circle :
    public AnimationCurve
{
private:
    float m_radius;
public:
    Circle(float radius, float period) {
        m_radius = radius;
        m_period = period;
    }

    glm::vec3 SamplePosition(float t);
    glm::quat SampleRotation(float t);
};