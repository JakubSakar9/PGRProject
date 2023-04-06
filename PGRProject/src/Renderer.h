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

	ShaderProgram::Shaders m_shaders;
	Scene m_scene;

	Renderer()
		: m_refreshRate(DEFAULT_REFRESH_RATE), m_lastTime(0) {
		m_refreshTimeMs = 1000.0f / m_refreshRate;
		m_shaders.defaultShader = new ShaderProgram("Shaders/simple-vs.glsl", "Shaders/simple-fs.glsl", SHADER_TYPE_DEFAULT);
		m_shaders.skyboxShader = new ShaderProgram("Shaders/skybox-vs.glsl", "Shaders/skybox-fs.glsl", SHADER_TYPE_SKYBOX);
	}
public:
	Renderer(const Renderer&) = delete;

	static Renderer& Get() {
		static Renderer s_Instance;
		return s_Instance;
	}

	bool Init();
	bool InitShaders();
	void Render();	
	void Update();

	inline unsigned int RefreshTimeMs() const { return m_refreshTimeMs; }
};

