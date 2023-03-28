#pragma once

#include "Light.h"

class PointLight : Light
{
private:
	glm::vec3 m_Attenuation;
	unsigned int m_Id;
public:
	PointLight() {}
	PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation);
	~PointLight() {}

	void Update(ShaderProgram* shaderProgram);
};

