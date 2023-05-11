#pragma once

#include "Object.h"

const ShaderType lightShaders[] = {
	SHADER_TYPE_DEFAULT,
	SHADER_TYPE_WATER
};

/// <summary>
/// An abstract class that represents any object in the scene that emits light.
/// </summary>
class Light :
	public ObjectInstance
{
protected:
	/// <summary>
	/// A 3D vector that represents color of the emitted light in a RGB format. All of its elements range between zero and one.
	/// </summary>
	glm::vec3 m_color;

	/// <summary>
	/// A value that describes the influence of the light on the scene illumination.
	/// </summary>
	float m_intensity;
public:
	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
	/// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) = 0;
};

