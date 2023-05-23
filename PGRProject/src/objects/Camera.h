//----------------------------------------------------------------------------------------
/**
 * \file       Camera.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once
#include <iostream>

#include "pgr.h"


#include "Object.h"
#include "../InputManager.h"
#include "../ShaderProgram.h"
#include "../BoxCollider.h"

#define DEFAULT_MOVEMENT_SPEED 1.0f
#define MOUSE_SENSITIVITY 0.4f

/// <summary>
/// Class that is used to represent any camera that can capture a scene and render it from that point of view. Because it is a subclass of the ObjecInstance class, it can be placed into the object hierarchy.
/// </summary>
class Camera
	: public ObjectInstance
{
private:
	/// <summary>
	/// 3D vector that contains element-wise lower bounds for space in which the given camera can move. Only relevant for a camera that is marked as dynamic.
	/// </summary>
	glm::vec3 m_lBound;

	/// <summary>
	/// 3D vector that contains element-wise upper bounds for space in which the given camera can move. Only relevant for a camera that is marked as dynamic.
	/// </summary>
	glm::vec3 m_uBound;

	/// <summary>
	/// Describes field of view of the camera in degrees for both x and y axis.
	/// </summary>
	float m_fovDegrees;

	/// <summary>
	/// Describes the distance of the near clipping plane of the camera from the camera center.
	/// </summary>
	float m_nearPlane;

	/// <summary>
	/// Describes the distance of the far clipping plane of the camera from the camera center.
	/// </summary>
	float m_farPlane;

	/// <summary>
	/// Describes the aspect ratio of the rendered image. Do not change if not necessary.
	/// </summary>
	float m_aspectRatio;

	/// <summary>
	/// Describes the distance the camera travels per one millisecond. The camera movement is calculated with respect to the local coordinate system of the parent object.
	/// </summary>
	float m_movementSpeed;

	/// <summary>
	/// A flag that describes if the given camera is dynamic. A dynamic camera can be controlled using keyboard and mouse.
	/// </summary>
	bool m_dynamic;

	/// <summary>
	/// A utility variable which uses a number to identify the camera. This identifier is used by other classes which cannot include the camera class directly to avoid link errors.
	/// </summary>
	int m_cameraId;

	/// <summary>
	/// Contains a vector of all colliders that are present in the active scene. This vector is updated every frame.
	/// </summary>
	static std::vector<BoxCollider*> s_colliders;
public:
	/// <summary>
	/// Default constructor of the Camera class. Used for debugging only.
	/// </summary>
	Camera();

	/// <summary>
	/// The Camera class constructor. Loads all camera parameters from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the ambient light data.</param>
	Camera(nlohmann::json source);

	/// <summary>
	/// Computes the view matrix which is used to transform to eye coordinates for all objects in the scene.
	/// </summary>
	/// <returns>A 4x4 matrix that represents the world to eye transformation for all objects.</returns>
	glm::mat4 ComputeViewMatrix();

	/// <summary>
	/// Computes the view matrix which is used to transform to eye coordinates for skybox. That means that the computed transformation does not involve any translation.
	/// </summary>
	/// <returns>A 4x4 matrix that represents the world to eye transformation for skybox.</returns>
	glm::mat4 ComputeSkyboxViewMatrix();

	/// <summary>
	/// Computes the projection matrix based on camera parameters
	/// </summary>
	/// <returns></returns>
	inline glm::mat4 ComputeProjectionMatrix() {
		return glm::perspective(glm::radians(m_fovDegrees), m_aspectRatio, m_nearPlane, m_farPlane);
	}

	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// 
	/// Updates camera parameters based on input and sends necessary information to all relevant shaders.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
	/// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// <summary>
	/// Updates boundaries for a dynamic camera.
	/// </summary>
	/// <param name="lBound">- new element-wise lower bounds for space in which the given camera can move.
	/// </summary></param>
	/// <param name="uBound"></param>
	void ChangeBounds(glm::vec3 lBound, glm::vec3 uBound);

	/// <summary>
	/// Returns local position of the camera.
	/// </summary>
	/// <returns></returns>
	inline glm::vec3 Position() { return m_position; }

	/// <summary>
	/// Updates the vector of colliders which are currently active and need to be detected by active cameras.
	/// </summary>
	/// <param name="colliders">Vector that contains colliders with parameters transformed to global coordinate system</param>
	static void UpdateColliders(std::vector<BoxCollider*> colliders);

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	void ShowProperties() override;
};

