#pragma once

#include <iostream>
#include <map>

#include "pgr.h"

#include "ShaderType.h"

#define DEFAULT_VS_SOURCE "Shaders/simple-vs.glsl"
#define DEFAULT_FS_SOURCE "Shaders/simple-fs.glsl"

class ShaderProgram
{
private:
	GLuint m_ProgramObject = 0;
public:
	struct Locations {
		// vertex attributes locations
		GLint position;
		GLint normal;
		GLint texCoords;

		// uniforms locations
		GLint pvmMatrix;
		GLint localCameraPosition;

		struct AmbientLight {
			GLint color;
			GLint intensity;
		} ambientLight;

		struct DirectionalLight {
			GLint color;
			GLint direction;
			GLint intensity;
		} directionalLight;

		GLint colDiffuse;
		GLint texDiffuse;
		GLint useTexDiffuse;

		GLint colSpecular;
		GLint specularExponent;
	};

	Locations locations;

private:
	bool LoadShaders();
	bool CreateShader(const std::string &vsSource, const std::string& fsSource);

public:
	ShaderProgram() {}
	~ShaderProgram() {}

	void UseShader();
	bool Init();
};

