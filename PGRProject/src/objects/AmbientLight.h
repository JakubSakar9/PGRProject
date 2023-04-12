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

	void Update(float deltaTime);
};

