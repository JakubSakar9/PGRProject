#pragma once

#include <iostream>
#include <map>

#include "pgr.h"

#include "ShaderType.h"

#define DEFAULT_VS_SOURCE "Shaders/simple-vs.glsl"
#define DEFAULT_FS_SOURCE "Shaders/simple-fs.glsl"

#define MAX_POINT_LIGHTS 4
#define MAX_SPOTLIGHTS 2

#define ATTRIB_LOC(s) CreateAttributeLocation(std::string(s), std::string(s))
#define UNIF_LOC(s) CreateUniformLocation(std::string(s), std::string("u_") + std::string(s))
#define PL_LOC(at, idx) {std::string str = std::string("pointLights[" + std::to_string(idx) + std::string("].") + std::string(at)); UNIF_LOC(str);}
#define SL_LOC(at, idx) {std::string str = std::string("spotlights[" + std::to_string(idx) + std::string("].") + std::string(at)); UNIF_LOC(str);}

class ShaderProgram
{
private:
	GLuint m_programObject = 0;
	std::map<std::string, GLint> m_locations;
	
	std::string m_vertexShaderPath;
	std::string m_fragmentShaderPath;

	ShaderType m_shaderType;
public:
	struct Shaders {
		ShaderProgram* defaultShader;
		ShaderProgram* skyboxShader;
	};

	static glm::vec3 s_cameraPosition;

	static glm::vec3 s_pointLightPositions[MAX_POINT_LIGHTS];
	static int s_nextPointLightIndex;

	static glm::vec3 s_spotlightPositions[MAX_SPOTLIGHTS];
	static int s_nextSpotlightIndex;

private:
	bool LoadShaders();
	bool LoadDefault();
	bool LoadSkybox();
	bool CreateShader(const std::string &vsSource, const std::string& fsSource);
	void InitPointLightLocations();
	void InitSpotlightLocations();
	void CreateAttributeLocation(std::string cName, std::string shaderName);
	void CreateUniformLocation(std::string cName, std::string shaderName);

public:
	ShaderProgram() {}
	inline ShaderProgram(std::string vsPath, std::string fsPath, ShaderType shaderType)
		: m_vertexShaderPath(vsPath)
		, m_fragmentShaderPath(fsPath)
		, m_shaderType(shaderType) {}

	void UseShader();
	bool Init();

	inline void SetUniform(std::string name, int x) {
		glUniform1i(GetLocation(name), x);
		CHECK_GL_ERROR();
	}

	inline void SetUniform(std::string name, float x) {
		glUniform1f(GetLocation(name), x);
		CHECK_GL_ERROR();
	}

	inline void SetUniform(std::string name, glm::vec3& v) {
		glUniform3f(GetLocation(name), v.x, v.y, v.z);
		CHECK_GL_ERROR();
	}

	inline void SetUniform(std::string name, glm::mat4x4& m) {
		glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(m));
		CHECK_GL_ERROR();
	}

	inline void EnableAttrib(std::string name) {
		glEnableVertexAttribArray(GetLocation(name));
		CHECK_GL_ERROR();
	}

	inline void AttribFloat(std::string name, int size, int stride, int offset) {
		glVertexAttribPointer(GetLocation(name), size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (offset * sizeof(float)));
		CHECK_GL_ERROR();
	}

	GLint GetLocation(std::string name);
};

