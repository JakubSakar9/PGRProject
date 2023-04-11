#pragma once

#include "pgr.h"

#include "objects/Object.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "objects/AmbientLight.h"
#include "objects/DirectionalLight.h"
#include "objects/PointLight.h"
#include "objects/Rupee.h"
#include "objects/Spotlight.h"
#include "Skybox.h"


class Scene
{
private:
	glm::mat4 m_RootModelMatrix;
	
	ObjectInstance m_rootObject;
	ObjectInstance m_seaObject;
	ObjectInstance m_linkObject;
	ObjectInstance m_birdObject;
	
	Rupee m_RupeeObject;

	Skybox m_skybox;

	AmbientLight m_AmbientLight;
	DirectionalLight m_DirectionalLight;

	PointLight m_pointLight1;
	PointLight m_pointLight2;
	PointLight m_pointLight3;
	PointLight m_pointLight4;

	Spotlight m_spotlight1;
	Spotlight m_spotlight2;

	Camera *m_ViewCamera;

	Camera m_DynamicCamera;
	Camera m_StaticCamera1;
	Camera m_StaticCamera2;
	
public:
	Scene();

	bool Init();
	void Render();
	void Update(float deltaTime);
	void SwitchCamera();
};

