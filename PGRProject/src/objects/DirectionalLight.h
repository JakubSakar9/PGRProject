#pragma once

#include "Light.h"

class DirectionalLight
	: public Light
{
private:
	glm::vec3 m_Direction;
public:
	DirectionalLight() {}
	DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction);
	~DirectionalLight() {}

	void Update(float deltaTime);
};