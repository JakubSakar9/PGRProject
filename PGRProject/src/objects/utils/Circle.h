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

    /// Calculates a position on the curve for the given parameter
    ///
    /// @param t is a time parameter that is used to parametrize the curve
    /// @return A position as a glm::vec3, which contains the local position of the sampled point for the given curve
    glm::vec3 SamplePosition(float t);

    /// Calculates a rotation on the curve for the given parameter
    ///
    /// @param t is a time parameter that is used to parametrize the curve
    /// @return A rotation as a glm::quat, which contains the local rotation of the sampled point for the given curve
    glm::quat SampleRotation(float t);

    /// Generates ImGui objects that will display properties of the curve
    void ShowProperties();
};