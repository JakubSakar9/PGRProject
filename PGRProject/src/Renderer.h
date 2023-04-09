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

	Renderer()
		: m_refreshRate(DEFAULT_REFRESH_RATE), m_lastTime(0) {
		m_refreshTimeMs = 1000.0f / m_refreshRate;

		ShaderProgram *defaultShader = new ShaderProgram("Shaders/default-vs.glsl",
			"Shaders/default-fs.glsl", SHADER_TYPE_DEFAULT);

		ShaderProgram* skyboxShader = new ShaderProgram("Shaders/skybox-vs.glsl",
			"Shaders/skybox-fs.glsl", SHADER_TYPE_SKYBOX);

		ShaderProgram* eyeShader = new ShaderProgram("Shaders/eye-vs.glsl",
			"Shaders/eye-fs.glsl", SHADER_TYPE_EYE);
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

