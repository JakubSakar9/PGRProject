//----------------------------------------------------------------------------------------
/**
 * \file       EmptyObject.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Camera.h"
#include "EyeObject.h"
#include "PointLight.h"
#include "Rupee.h"
#include "Spotlight.h"
#include "StaticObject.h"
#include "Water.h"
#include "utils/Circle.h"

/// <summary>
/// This class describes an object that is used to provide a level of hierarchy to the scene or define an animation path for all child objects. It is not used to render any objects on the screen.
/// It is also the only object type that supports loading children from the JSON file.
/// </summary>
class EmptyObject :
	public ObjectInstance
{
private:
	AnimationCurve* m_curve = nullptr;
	float m_time;

	/// <summary>
	/// Function that computes a matrix that transforms given object from its model coordinates to the local coordinate system of its parent.
	/// </summary>
	/// <returns>A 4x4 matrix which represents the transformation.</returns>
	glm::mat4 ComputeModelMatrix(float time);

	/// <summary>
	/// A helper function that is used to load children of the empty object.
	/// </summary>
	/// <param name="source">- JSON object that contains the empty object data</param>
	void InitChildren(nlohmann::json source);
public:
	/// <summary>
	/// Default constructor for the EmptyObject class. Do not use.
	/// </summary>
	EmptyObject() {}

	/// <summary>
	/// The EmptyObject class constructor. Used to load the empty object from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the empty object data.</param>
	EmptyObject(nlohmann::json source);

	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
	/// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	void ShowProperties() override;
};

