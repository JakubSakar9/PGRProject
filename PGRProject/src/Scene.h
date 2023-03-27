#pragma once

#include "pgr.h"

#include "objects/Object.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "objects/AmbientLight.h"
#include "objects/DirectionalLight.h"

class Scene
{
private:
	glm::mat4 m_RootModelMatrix;
	
	ObjectInstance m_RootObject;
	ObjectInstance m_SeaObject;
	ObjectInstance m_LinkObject;

	AmbientLight m_AmbientLight;
	DirectionalLight m_DirectionalLight;

	Camera m_ViewCamera;
	
public:
	Scene();

	bool Init(ShaderProgram *shaderProgram);
	void Render(ShaderProgram *shaderProgram);
	void Update(float deltaTime, ShaderProgram *shaderProgram);
};

