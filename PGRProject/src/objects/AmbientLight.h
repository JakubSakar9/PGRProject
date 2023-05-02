#include "../utils/json.hpp"

#include "Light.h"

#pragma once
class AmbientLight
	: public Light
{
public:
	AmbientLight() {}
	AmbientLight(glm::vec3 color, float ambientIntensity);
	AmbientLight(nlohmann::json source);
	~AmbientLight() {}

	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	void ShowProperties() override;

	void RenderGraph() override;
};

