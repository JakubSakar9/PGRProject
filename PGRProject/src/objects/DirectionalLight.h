#pragma once

#include "../utils/json.hpp"

#include "Light.h"

class DirectionalLight
	: public Light
{
private:
	glm::vec3 m_Direction;
public:
	DirectionalLight() {}
	DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction);
	DirectionalLight(nlohmann::json source);
	~DirectionalLight() {}

	void Update(float deltaTime, const glm::mat4* parentModelMatrix);
};