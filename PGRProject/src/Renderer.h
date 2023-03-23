#pragma once

#include "pgr.h"

#include "objects/Object.h"
#include "Scene.h"

#define DEFAULT_REFRESH_RATE 30

class Renderer
{
private:
	int m_RefreshRate;
	unsigned int m_RefreshTimeMs;
	float m_LastTime;

	ShaderProgram m_ShaderProgram;
	Scene m_Scene;

	Renderer()
		: m_RefreshRate(DEFAULT_REFRESH_RATE), m_LastTime(0) {
		m_RefreshTimeMs = 1000.0f / m_RefreshRate;
	}
public:
	Renderer(const Renderer&) = delete;

	static Renderer& Get() {
		static Renderer s_Instance;
		return s_Instance;
	}

	bool Init();
	void Render();	
	void Update();

	inline unsigned int RefreshTimeMs() const { return m_RefreshTimeMs; }
};

