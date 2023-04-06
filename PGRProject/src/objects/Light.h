#pragma once

#include "Object.h"

class Light :
	public ObjectInstance
{
protected:
	glm::vec3 m_Color;
	float m_Intensity;
public:
	virtual void Update(ShaderProgram* shaderProgram) = 0;
};

