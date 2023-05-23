//----------------------------------------------------------------------------------------
/**
 * \file       Scene.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

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
	/// <summary>
	/// Pointer to the scene that is currently in use.
	/// </summary>
	static Scene* s_usedScene;

	/// <summary>
	/// Parent model matrix that will be used for the root object. Typically set to identity matrix.
	/// </summary>
	glm::mat4 m_rootModelMatrix;
	
	/// <summary>
	/// An object that contains most of the scene hierarchy with the exception of ambient light and directional light.
	/// </summary>
	EmptyObject m_rootObject;

	/// <summary>
	/// Pointer to the object that is currently selected in the scene graph.
	/// </summary>
	ObjectInstance* m_selectedObject = nullptr;

	/// <summary>
	/// Skybox of the given scene. Path to the source images is hardcoded.
	/// </summary>
	Skybox m_skybox;

	/// <summary>
	/// Ambient light that is present in the scene. Not a part of the scene hierarchy.
	/// </summary>
	AmbientLight m_AmbientLight;


	/// <summary>
	/// Ambient light that is present in the scene. Not a part of the scene hierarchy.
	/// </summary>
	DirectionalLight m_DirectionalLight;

	/// <summary>
	/// A list of all objects that are transparent and will be rendered in the second pass of the rendering pipeline.
	/// </summary>
	std::vector<ObjectInstance*> m_transparentObjects;

	/// <summary>
	/// ID of the camera that is currenty used to render the scene.
	/// </summary>
	int m_selectedCamera;
	
public:
	/// <summary>
	/// Default constructor for the Scene class. Do not use.
	/// </summary>
	Scene() {}

	/// <summary>
	/// The Scene class constructor. That is used to load the scene from the JSON file.
	/// </summary>
	/// <param name="name">Name of the scene which is the same as the filename of the source JSON file without the extension.</param>
	Scene(std::string name);

	/// <summary>
	/// Returns a pointer to the scene that is currently being rendered.
	/// </summary>
	/// <returns>A pointer to the scene that is currently being rendered.</returns>
	static Scene* Get() {
		return s_usedScene;
	}
	
	/// <summary>
	/// Initializes every object that is present in the scene.
	/// </summary>
	/// <returns>True if scene initialization went well, false otherwise.</returns>
	bool Init();

	/// <summary>
	/// Draws all objects that are part of the scene.
	/// </summary>
	void Render();

	/// <summary>
	/// Renders all objects that are partially or fully transparent. This rendering is done after all other objects have been already rendered.
	/// </summary>
	void RenderTransparent();

	/// <summary>
	/// Updates every object that is present in the scene.
	/// </summary>
	/// <param name="deltaTime"></param>
	void Update(float deltaTime);

	/// <summary>
	/// Queries InputManager for camera switch commands and switches the camera based on these commands.
	/// <list type="bullet">
	///		<item>0 - the dynamic camera is selected.</item>
	///		<item>1 - selects next camera in order.</item>
	///		<item>2 - selects previous camera in order.</item>
	///		<item>-1 - no action is performed.</item>
	///	</list>
	/// </summary>
	void SwitchCamera();

	/// <summary>
	/// Renders the graph of the scene, which includes ambient and directional light.
	/// </summary>
	void RenderGraph();

	/// <summary>
	/// Renders content of the properties window.
	/// </summary>
	void ShowProperties();
};

