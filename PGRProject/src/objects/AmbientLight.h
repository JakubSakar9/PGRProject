#include "Light.h"

#pragma once
class AmbientLight
	: public Light
{
public:
	AmbientLight() {}
	AmbientLight(glm::vec3 color, float ambientIntensity);
	~AmbientLight() {}

	void Update(float deltaTime);
};

