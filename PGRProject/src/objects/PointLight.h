#pragma once

#include "Light.h"

class PointLight : Light
{
public:
	struct Attenuation {
		float constant;
		float linear;
		float quadratic;
	};
	Attenuation m_Attenuation;
public:
	PointLight() {}
	PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation);
	~PointLight() {}

	void Update(ShaderProgram* shaderProgram);
};

