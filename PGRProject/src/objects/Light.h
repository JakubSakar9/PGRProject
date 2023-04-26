#pragma once

#include "Object.h"

const ShaderType lightShaders[] = {
	SHADER_TYPE_DEFAULT,
	SHADER_TYPE_WATER
};

class Light :
	public ObjectInstance
{
protected:
	glm::vec3 m_Color;
	float m_Intensity;
public:
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix) = 0;
};

