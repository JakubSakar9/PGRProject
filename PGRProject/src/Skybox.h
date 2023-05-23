//----------------------------------------------------------------------------------------
/**
 * \file       Skybox.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "pgr.h"

#include "ShaderProgram.h"

#define ATTRIBS_PER_VERTEX 3
#define SKYBOX_DIR_PREFIX std::string("misc/skybox/")

const float skyboxVertices[] = {
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f
};

const unsigned int skyboxIndices[] = {
	0, 5, 1,
	0, 4, 5,
	1, 2, 0,
	1, 3, 2,
	0, 2, 4,
	4, 2, 6,
	4, 6, 5,
	5, 6, 7,
	5, 7, 3,
	5, 3, 1,
	3, 7, 2,
	7, 6, 2
};


/// <summary>
/// A class that represents the skybox that is rendered in the background of the scene.
/// </summary>
class Skybox
{
private:
	/// <summary>
	/// A struct that contains all OpenGL objects that will be used for the skybox geometry.
	/// </summary>
	typedef struct _SkyboxGeometry {
		GLuint vertexBufferObject;
		GLuint elementBufferObject;
		GLuint vertexArrayObject;
	} SkyboxGeometry;

	SkyboxGeometry m_geometry;

	/// <summary>
	/// OpenGL identifier for the skybox texture.
	/// </summary>
	GLuint m_cubemapTex;
public:
	/// <summary>
	/// Default constructor for the Skybox class. The only way to create the skybox as all of its parameters are hardcoded.
	/// </summary>
	Skybox() {}

	/// <summary>
	/// Initializes all OpenGL objects for the skybox.
	/// </summary>
	void GenSkybox();

	/// <summary>
	/// Renders the skybox on the screen.
	/// </summary>
	void Draw();

	/// <summary>
	/// Loads the cubemap texture that will be used for the skybox.
	/// </summary>
	void LoadCubemap();
};

