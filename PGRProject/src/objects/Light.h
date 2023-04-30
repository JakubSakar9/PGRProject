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
	glm::vec3 m_color;
	float m_intensity;
public:
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) = 0;
};

