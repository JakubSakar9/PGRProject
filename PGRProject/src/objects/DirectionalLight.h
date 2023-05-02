#pragma once

#include "../utils/json.hpp"

#include "Light.h"

class DirectionalLight
	: public Light
{
private:
	glm::vec3 m_direction;
public:
	DirectionalLight() {}
	DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction);
	DirectionalLight(nlohmann::json source);
	~DirectionalLight() {}

	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	void ShowProperties() override;

	void RenderGraph() override;
};