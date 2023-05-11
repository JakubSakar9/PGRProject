#pragma once

#include "../utils/json.hpp"

#include "Light.h"

/// A class that describes a light that illuminates the entire scene in the same direction at its every point. It is also one of the objects that cannot be loaded as a part of scene hierarchy and needs to be defined on its highest level.
class DirectionalLight
	: public Light
{
private:
	/// <summary>
	/// A 3D vector that describes the direction of the light rays for the directional light. Its magnitude has no influence on the scene illumination with the exception of the zero vector.
	/// </summary>
	glm::vec3 m_direction;
public:
	/// <summary>
	/// Default constructor for the DirectionalLight class. Do not use.
	/// </summary>
	DirectionalLight() {}

	/// <summary>
	/// The DirectionalLight class constructor. Suitable for debugging.
	/// </summary>
	/// <param name="color">- light color in RGB format. All of its elements range between zero and one.</param>
	/// <param name="intensity">- intensity of the directional light. It is used to scale the impact of the ambient light in the scene.</param>
	/// <param name="direction">- direction of the directional light rays.</param>
	DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction);

	/// <summary>
	/// The DirectionalLight class constructor. Used to load the directional light from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the directional light data.</param>
	DirectionalLight(nlohmann::json source);

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

	/// <summary>
	/// Renders nodes for the current object and all of its children into the scene graph.
	/// </summary>
	void RenderGraph() override;
};