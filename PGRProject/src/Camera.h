#pragma once
#include <iostream>

#include "pgr.h"

#include "InputManager.h"

#define DEFAULT_MOVEMENT_SPEED 1.0f
#define MOUSE_SENSITIVITY 0.4f

class Camera
{
private:
	glm::vec3 m_Position;
	glm::quat m_Rotation;

	float m_FovDegrees, m_NearPlane, m_FarPlane, m_AspectRatio;
	float m_MovementSpeed;
public:
	inline Camera()
		: m_FovDegrees(90.0f)
		, m_NearPlane(0.01f)
		, m_FarPlane(1000.0f)
		, m_AspectRatio(1.0f)
		, m_MovementSpeed(DEFAULT_MOVEMENT_SPEED)
	{}

	inline Camera(glm::vec3 position)
		: m_FovDegrees(90.0f)
		, m_NearPlane(0.01f)
		, m_FarPlane(1000.0f)
		, m_AspectRatio(1.0f)
		, m_Position(position)
		, m_MovementSpeed(DEFAULT_MOVEMENT_SPEED)
	{}
	
	inline Camera(glm::vec3 position, glm::quat rotation)
		: m_FovDegrees(90.0f)
		, m_NearPlane(0.01f)
		, m_FarPlane(1000.0f)
		, m_AspectRatio(1.0f)
		, m_Position(position)
		, m_Rotation(rotation)
		, m_MovementSpeed(DEFAULT_MOVEMENT_SPEED)
	{}
	
	inline Camera(glm::vec3 position, glm::quat rotation, float fov, float near, float far)
		: m_FovDegrees(fov)
		, m_NearPlane(near)
		, m_FarPlane(far)
		, m_AspectRatio(1.0f)
		, m_Position(position)
		, m_Rotation(rotation)
		, m_MovementSpeed(DEFAULT_MOVEMENT_SPEED)
	{}

	glm::mat4 ComputeViewMatrix();

	inline glm::mat4 ComputeProjectionMatrix() {
		return glm::perspective(glm::radians(m_FovDegrees), 1.0f, m_NearPlane, m_FarPlane);
	}

	bool Init();

	void Update(float deltaTime);
};

