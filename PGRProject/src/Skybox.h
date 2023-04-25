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

class Skybox
{
private:
	typedef struct _SkyboxGeometry {
		GLuint vertexBufferObject;
		GLuint elementBufferObject;
		GLuint vertexArrayObject;
	} SkyboxGeometry;

	SkyboxGeometry m_geometry;
	GLuint m_cubemapTex;
public:
	Skybox() {}

	void GenSkybox();

	void Draw();

	void LoadCubemap();
};

