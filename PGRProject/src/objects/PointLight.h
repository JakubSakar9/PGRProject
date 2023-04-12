#pragma once

#include "../utils/json.hpp"

#include "Light.h"

#define PL(at, idx) std::string("pointLights[") + std::to_string(idx) + std::string("].") + std::string(at)

class PointLight
	: public Light
{
private:
	glm::vec3 m_attenuation;
	unsigned int m_id;
public:
	PointLight() {}
	PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation);
	PointLight(nlohmann::json source);
	~PointLight() {}

	void Update(float deltaTime);
};

