#pragma once

#include <iostream>

#include <cmath>

#include "../../imgui/imgui.h"
#include "pgr.h"

class AnimationCurve {
protected:
	/// <summary>
	/// Describes the amount by which the parameter value has to be changed in order to loop around the curve
	/// </summary>
	float m_period;
public:

	/// Calculates a position on the curve for the given parameter
	///
	/// @param t is a time parameter that is used to parametrize the curve
	/// @return A position as a glm::vec3, which contains the local position of the sampled point for the given curve
	virtual glm::vec3 SamplePosition(float t) = 0;

	/// Calculates a rotation on the curve for the given parameter
	///
	/// @param t is a time parameter that is used to parametrize the curve
	/// @return A rotation as a glm::quat, which contains the local rotation of the sampled point for the given curve
	virtual glm::quat SampleRotation(float t) = 0;
	
	/// Generates ImGui objects that will display properties of the curve
	virtual void ShowProperties() = 0;
};