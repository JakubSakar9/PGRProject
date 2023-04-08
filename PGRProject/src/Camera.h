#pragma once
#include <iostream>

#include "pgr.h"

#include "InputManager.h"
#include "ShaderProgram.h"
#include "BoxCollider.h"

#define DEFAULT_MOVEMENT_SPEED 1.0f
#define MOUSE_SENSITIVITY 0.4f

class Camera
{
private:
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_lBound;
	glm::vec3 m_uBound;

	float m_FovDegrees, m_NearPlane, m_FarPlane, m_AspectRatio;
	float m_MovementSpeed;
	bool m_dynamic;
public:
	inline Camera()
		: m_FovDegrees(90.0f)
		, m_NearPlane(0.01f)
		, m_FarPlane(1000.0f)
		, m_AspectRatio(1.0f)
		, m_Position(glm::vec3(0.0f))
		, m_lBound(glm::vec3(0.0f))
		, m_uBound(glm::vec3(0.0f))
		, m_MovementSpeed(DEFAULT_MOVEMENT_SPEED)
		, m_dynamic(false)
	{}
	
	inline Camera(glm::vec3 position, bool dynamic)
		: m_FovDegrees(90.0f)
		, m_NearPlane(0.01f)
		, m_FarPlane(1000.0f)
		, m_AspectRatio(1.0f)
		, m_Position(position)
		, m_lBound(glm::vec3(0.0f))
		, m_uBound(glm::vec3(0.0f))
		, m_MovementSpeed(DEFAULT_MOVEMENT_SPEED)
		, m_dynamic(dynamic)
	{}

	glm::mat4 ComputeViewMatrix();
	glm::mat4 ComputeSkyboxViewMatrix();

	inline glm::mat4 ComputeProjectionMatrix() {
		return glm::perspective(glm::radians(m_FovDegrees), 1.0f, m_NearPlane, m_FarPlane);
	}

	bool Init();

	void Update(ShaderProgram *shaderProgram, std::vector<BoxCollider*> colliders, float deltaTime);

	void ChangeBounds(glm::vec3 lBound, glm::vec3 uBound);

	inline glm::vec3 Position() { return m_Position; }
};

