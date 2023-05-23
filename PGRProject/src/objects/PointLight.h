//----------------------------------------------------------------------------------------
/**
 * \file       PointLight.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "../utils/json.hpp"

#include "Light.h"

#define PL(at, idx) std::string("pointLights[") + std::to_string(idx) + std::string("].") + std::string(at)

/// <summary>
/// A class for a light source that illuminates the scene from a single point.
/// </summary>
class PointLight
	: public Light
{
private:
	/// <summary>
	/// A 3D vector that contains coefficients of the illumination function.
	/// Because the attenuation function that was used in this program was quadratic, the first coefficient is constant, the second coefficient is linear and the third coefficient is quadratic.
	/// </summary>
	glm::vec3 m_attenuation;

	/// <summary>
	/// A unique identifier for the point light, which is used by shaders.
	/// </summary>
	unsigned int m_id;

	/// <summary>
	/// Frequency of point light pulses in kHz. If set to 0, no pulses occur.
	/// </summary>
	float m_pulseFrequency = 0.0f;

	/// <summary>
	/// Value that makes the pulses less aggressive as the value increases. Values that are less than one will be automatically clamped to one.
	/// </summary>
	float m_pulseSmoothness = 1.0f;

	/// <summary>
	/// A helper attribute that holds the elapsed time in milliseconds from since point light has been added to the scene.
	/// </summary>
	float m_time = 0.0f;
public:
	/// <summary>
	/// Default constructor for the PointLight class. Do not use.
	/// </summary>
	PointLight() {}

	/// <summary>
	/// The PointLight class constructor. Suitable for debugging.
	/// </summary>
	/// <param name="color">- light color in RGB format. All of its elements range between zero and one.</param>
	/// <param name="intensity">- intensity of the directional light. It is used to scale the impact of the ambient light in the scene.</param>
	/// <param name="position">- local position of the light source.</param>
	/// <param name="attenuation">- coefficients of the quadratic attenuation function.</param>
	PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation);

	/// <summary>
	/// The PointLight class constructor. Used to load the point light from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the point light data.</param>
	PointLight(nlohmann::json source);

	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
	/// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) override;

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	void ShowProperties() override;
};

