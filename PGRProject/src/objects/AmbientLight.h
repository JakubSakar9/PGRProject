#include "Light.h"

#pragma once
class AmbientLight : Light
{
public:
	AmbientLight() {}
	AmbientLight(glm::vec3 color, float ambientIntensity);
	~AmbientLight() {}

	void Update(ShaderProgram *shaderProgram);
};

