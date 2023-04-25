#pragma once

#include "pgr.h"

#include "objects/Object.h"
#include "objects/Camera.h"
#include "ResourceManager.h"
#include "objects/AmbientLight.h"
#include "objects/DirectionalLight.h"
#include "objects/PointLight.h"
#include "objects/Rupee.h"
#include "objects/Spotlight.h"
#include "Skybox.h"
#include "objects/EmptyObject.h"


class Scene
{
private:
	static Scene* s_usedScene;

	glm::mat4 m_rootModelMatrix;
	
	EmptyObject m_rootObject;

	Skybox m_skybox;

	AmbientLight m_AmbientLight;
	DirectionalLight m_DirectionalLight;

	int m_selectedCamera;
	
public:
	Scene() {}

	Scene(std::string name);

	static Scene* Get() {
		return s_usedScene;
	}
	
	bool Init();
	void Render();
	void Update(float deltaTime);
	void SwitchCamera();
};

