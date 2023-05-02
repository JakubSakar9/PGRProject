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
	float m_pulseFrequency;
	float m_pulseSmoothness;
	float m_time = 0.0f;
public:
	PointLight() {}
	PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation);
	PointLight(nlohmann::json source);
	~PointLight() {}

	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) override;

	void ShowProperties() override;
};

