#pragma once

#include "pgr.h"

#include "Object.h"
#include "Camera.h"
#include "ResourceManager.h"

class Scene
{
private:
	glm::mat4 m_RootModelMatrix;
	
	ObjectInstance m_RootObject;
	Camera m_ViewCamera;
	
public:
	Scene();

	bool Init(ShaderProgram *shaderProgram);
	void Render(ShaderProgram *shaderProgram);
	void Update(float deltaTime);
};

