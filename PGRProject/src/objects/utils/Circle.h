//----------------------------------------------------------------------------------------
/**
 * \file       Circle.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once
#include "AnimationCurve.h"

/// <summary>
/// Class that is used to describe a circular animation curve
/// </summary>
class Circle :
    public AnimationCurve
{
private:
    float m_radius;
public:
    /// <summary>
    /// The only constructor of the Circle class.
    /// </summary>
    /// <param name="radius">- radius of the circular path.</param>
    /// <param name="period">- parameter that describes the amount by which the parameter value has to be changed in order to loop around the curve</param>
    Circle(float radius, float period) {
        m_radius = radius;
        m_period = period;
    }

    /// <summary>
    /// Calculates a position on the curve for the given parameter.
    /// </summary>
    /// <param name="t">- time parameter that is used to parametrize the curve.</param>
    /// <returns>A position as a glm::vec3, which contains the local position of the sampled point for the given curve.</returns>
    glm::vec3 SamplePosition(float t);

    /// <summary>
    /// Calculates a rotation on the curve for the given parameter
    /// </summary>
    /// <param name="t">- time parameter that is used to parametrize the curve</param>
    /// <returns>A rotation as a glm::quat, which contains the local rotation of the sampled point for the given curve</returns>
    glm::quat SampleRotation(float t);

    /// <summary>
    /// Generates ImGui objects that will display properties of the curve
    /// </summary>
    void ShowProperties();
};