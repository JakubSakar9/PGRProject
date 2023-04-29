#pragma once

#include "pgr.h"

#include "objects/Object.h"
#include "Scene.h"

#define DEFAULT_REFRESH_RATE 30

class Renderer
{
private:
	int m_refreshRate;
	unsigned int m_refreshTimeMs;
	float m_lastTime;

	Scene m_scene;

	Renderer();
public:
	Renderer(const Renderer&) = delete;

	static Renderer& Get() {
		static Renderer s_instance;
		return s_instance;
	}

	bool Init();
	bool InitShaders();
	void Render();	
	void Update();

	inline unsigned int RefreshTimeMs() const { return m_refreshTimeMs; }
};

