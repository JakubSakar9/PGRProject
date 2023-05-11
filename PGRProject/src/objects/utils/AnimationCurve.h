#pragma once

#include <iostream>

#include <cmath>

#include "../../imgui/imgui.h"
#include "pgr.h"

/// <summary>
/// Abstract class that is used to describe any closed curve that an object can move along
/// </summary>
class AnimationCurve {
protected:
	/// <summary>
	/// Describes the amount by which the parameter value has to be changed in order to loop around the curve
	/// </summary>
	float m_period;
public:
	/// <summary>
	/// Calculates a position on the curve for the given parameter.
	/// </summary>
	/// <param name="t">is a time parameter that is used to parametrize the curve.</param>
	/// <returns>A position as a glm::vec3, which contains the local position of the sampled point for the given curve.</returns>
	virtual glm::vec3 SamplePosition(float t) = 0;
	
	/// <summary>
	/// Calculates a rotation on the curve for the given parameter
	/// </summary>
	/// <param name="t">is a time parameter that is used to parametrize the curve</param>
	/// <returns>A rotation as a glm::quat, which contains the local rotation of the sampled point for the given curve</returns>
	virtual glm::quat SampleRotation(float t) = 0;

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	virtual void ShowProperties() = 0;
};