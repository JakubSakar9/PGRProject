#pragma once
#include <iostream>

#include "pgr.h"


#include "Object.h"
#include "../InputManager.h"
#include "../ShaderProgram.h"
#include "../BoxCollider.h"

#define DEFAULT_MOVEMENT_SPEED 1.0f
#define MOUSE_SENSITIVITY 0.4f

class Camera
	: public ObjectInstance
{
private:
	glm::vec3 m_lBound;
	glm::vec3 m_uBound;

	float m_fovDegrees, m_nearPlane, m_farPlane, m_aspectRatio;
	float m_movementSpeed;
	bool m_dynamic;

	int m_cameraId;

	static std::vector<BoxCollider*> s_colliders;
public:
	Camera();
	Camera(nlohmann::json source);

	glm::mat4 ComputeViewMatrix();
	glm::mat4 ComputeSkyboxViewMatrix();

	inline glm::mat4 ComputeProjectionMatrix() {
		return glm::perspective(glm::radians(m_fovDegrees), 1.0f, m_nearPlane, m_farPlane);
	}

	bool GenObjects();

	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	void ChangeBounds(glm::vec3 lBound, glm::vec3 uBound);

	inline glm::vec3 Position() { return m_position; }

	static void UpdateColliders(std::vector<BoxCollider*> colliders);
};

