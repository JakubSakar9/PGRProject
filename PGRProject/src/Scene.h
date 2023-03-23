#pragma once

#include "pgr.h"

#include "objects/Object.h"
#include "Camera.h"
#include "ResourceManager.h"

class Scene
{
private:
	glm::mat4 m_RootModelMatrix;
	
	ObjectInstance m_RootObject;
	ObjectInstance m_SeaObject;
	Camera m_ViewCamera;
	
public:
	Scene();

	bool Init(ShaderProgram *shaderProgram);
	void Render(ShaderProgram *shaderProgram);
	void Update(float deltaTime);
};

