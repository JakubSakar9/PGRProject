#include "../utils/json.hpp"

#include "Light.h"

#pragma once

/// <summary>
/// A class that describes a light that illuminates the entire scene equally at its every point. It is also one of the objects that cannot be loaded as a part of scene hierarchy and needs to be defined on its highest level.
/// </summary>
class AmbientLight
	: public Light
{
public:
	
	/// <summary>
	/// Default constructor for the AmbientLight class. Do not use.
	/// </summary>
	AmbientLight() {}

	/// <summary>
	/// The AmbientLight class constructor. Suitable for debugging.
	/// </summary>
	/// <param name="color">- light color in RGB format. All of its elements range between zero and one.</param>
	/// <param name="ambientIntensity">- intensity of the ambient light. It is used to scale the impact of the ambient light in the scene.</param>
	AmbientLight(glm::vec3 color, float ambientIntensity);

	/// <summary>
	/// The AmbientLight class constructor. Used to load the ambient light from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the ambient light data.</param>
	AmbientLight(nlohmann::json source);

	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates. If set to nullptr, an identity matrix is considered.</param>
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

