#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glut.h"
#include "pgr.h"

#include "objects/Object.h"
#include "Scene.h"

#define DEFAULT_REFRESH_RATE 30

/// <summary>
/// A class that manages rendering loop and rendering configuration.
/// </summary>
class Renderer
{
private:
	/// <summary>
	/// Number of new frames that are rendered in one second.
	/// </summary>
	int m_refreshRate;

	unsigned int m_refreshTimeMs;

	/// <summary>
	/// Keeps track of elapsed time in milliseconds that was detected in the last loop.
	/// </summary>
	float m_lastTime;

	/// <summary>
	/// The scene that is currently rendered.
	/// </summary>
	Scene m_scene;

	/// <summary>
	/// The constructor for the Renderer class. Setups render loop, loads all shaders and the scene that is to be rendered.
	/// </summary>
	Renderer();
public:
	Renderer(const Renderer&) = delete;

	/// <summary>
	/// Getter for the singleton instance of the Renderer class.
	/// </summary>
	/// <returns>A renderer instance.</returns>
	static Renderer& Get() {
		static Renderer s_instance;
		return s_instance;
	}

	/// <summary>
	/// Initializes scene and shaders. Sets OpenGL rendering options.
	/// </summary>
	/// <returns></returns>
	bool Init();

	/// <summary>
	/// Iterates through all shader programs and initializes them.
	/// </summary>
	/// <returns></returns>
	bool InitShaders();

	/// <summary>
	/// Draws everything on the screen. Called for each render iteration.
	/// </summary>
	void Render();

	/// <summary>
	/// Updates the scene. Called for every update iteration and computes time for the render iteration.
	/// </summary>
	void Update();

	/// <summary>
	/// Renders all GUI, if it is currently enabled, using the ImGui library.
	/// </summary>
	void RenderGui();

	inline unsigned int RefreshTimeMs() const { return m_refreshTimeMs; }
};

