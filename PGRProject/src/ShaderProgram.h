#pragma once

#include <iostream>
#include <map>

#include "pgr.h"

#include "ShaderType.h"

#define DEFAULT_VS_SOURCE "Shaders/simple-vs.glsl"
#define DEFAULT_FS_SOURCE "Shaders/simple-fs.glsl"

#define MAX_POINT_LIGHTS 4

class ShaderProgram
{
private:
	GLuint m_ProgramObject = 0;
public:
	struct PointLightLocations {
		GLint color;
		GLint intensity;
		GLint position;
		GLint attenuation;
	};
	
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

		PointLightLocations pointLights[MAX_POINT_LIGHTS];

		GLint colDiffuse;
		GLint texDiffuse;
		GLint useTexDiffuse;

		GLint colSpecular;
		GLint specularExponent;
	};

	Locations locations;

	static glm::vec3 s_cameraPosition;
	static glm::vec3 s_pointLightPositions[MAX_POINT_LIGHTS];
	static int s_nextPointLightIndex;

private:
	bool LoadShaders();
	bool CreateShader(const std::string &vsSource, const std::string& fsSource);
	void InitPointLightLocations();

public:
	ShaderProgram() {}
	~ShaderProgram() {}

	void UseShader();
	bool Init();
};

