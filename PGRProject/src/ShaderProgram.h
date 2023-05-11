#pragma once

#include <iostream>
#include <map>

#include "pgr.h"

#include "ShaderType.h"

#define DEFAULT_VS_SOURCE "Shaders/simple-vs.glsl"
#define DEFAULT_FS_SOURCE "Shaders/simple-fs.glsl"

#define MAX_POINT_LIGHTS 10
#define MAX_SPOTLIGHTS 2

#define ATTRIB_LOC(s) CreateAttributeLocation(std::string(s), std::string(s))
#define UNIF_LOC(s) CreateUniformLocation(std::string(s), std::string("u_") + std::string(s))
#define PL_LOC(at, idx) {std::string str = std::string("pointLights[" + std::to_string(idx) + std::string("].") + std::string(at));UNIF_LOC(str);}
#define SL_LOC(at, idx) {std::string str = std::string("spotlights[" + std::to_string(idx) + std::string("].") + std::string(at)); UNIF_LOC(str);}
#define SH(st) ShaderProgram::GetShader(st)

/// <summary>
/// A class that provides an abstraction layer for shaders. This involves creating new shaders from file, creating uniform and attribute locations and
/// setting up attributes and uniforms.
/// </summary>
class ShaderProgram
{
private:
	/// <summary>
	/// Shader program object for the current shader program.
	/// </summary>
	GLuint m_programObject = 0;

	/// <summary>
	/// Map that maps name of the uniforms and attributes to their respective locations.
	/// </summary>
	std::map<std::string, GLint> m_locations;
	
	/// <summary>
	/// Relative path to the vertex shader source file with respect to the project directory.
	/// </summary>
	std::string m_vertexShaderPath;

	/// <summary>
	/// Relative path to the vertex shader source file with respect to the project directory.
	/// </summary>
	std::string m_fragmentShaderPath;

	ShaderType m_shaderType;

	/// <summary>
	/// A helper flag that is set to true once the shader and its locations have been initialized.
	/// </summary>
	bool m_ready = false;

	/// <summary>
	/// A map that maps each shader type to its respective shader program. Used to easily make shader programs accessible accros the entire project.
	/// </summary>
	static std::map<ShaderType, ShaderProgram*> s_shaders;
public:
	/// <summary>
	/// A helper variable that contains the index that will be assigned to the next point light that is added to the scene.
	/// </summary>
	static int s_nextPointLightIndex;

	/// <summary>
	/// A helper variable that contains the index that will be assigned to the next spotlight that is added to the scene.
	/// </summary>
	static int s_nextSpotlightIndex;

	/// <summary>
	/// A helper variable that contains the index that will be assigned to the next static camera that is added to the scene.
	/// </summary>
	static int s_nextCameraIndex;

	/// <summary>
	/// A helper variable that contains the index of the camera that is currently being used to render the active scene.
	/// </summary>
	static int s_activeCameraIndex;

	/// <summary>
	/// A 3D vector that contains the position of the active camera in global coordinate system. This vector is passed to all relevant shaders in order to compute lighting.
	/// </summary>
	static glm::vec3 s_activeCameraPosition;

private:
	/// <summary>
	/// A function that compiles shaders from their source files and initializes their locations.
	/// </summary>
	/// <returns>True if shader loading is successful, false otherwise.</returns>
	bool LoadShaders();

	/// <summary>
	/// A function that creates all locations that are present in shaders which perform physically basde rendering.
	/// </summary>
	/// <returns>True if location creation is successful, false otherwise.</returns>
	bool LoadBasePBR();

	/// <summary>
	/// A function that creates all locations of the default shader.
	/// </summary>
	/// <returns>True if location creation is successful, false otherwise.</returns>
	bool LoadDefault();

	/// <summary>
	/// A function that creates all locaions of the skybox shader.
	/// </summary>
	/// <returns>True if location creation is successful, false otherwise.</returns>
	bool LoadSkybox();

	/// <summary>
	/// A function that creates all locations of the eye shader.
	/// </summary>
	/// <returns>True if location creation is successful, false otherwise.</returns>
	bool LoadEye();

	/// <summary>
	/// A function that creates all locations of the water shader.
	/// </summary>
	/// <returns>True if location creation is successful, false otherwise.</returns>
	bool LoadWater();

	/// <summary>
	/// A function that creates a shader program based on the vertex and fragment shader sources.
	/// </summary>
	/// <param name="vsSource">- relative path to the vertex shader source file with respect to the project directory.</param>
	/// <param name="fsSource">- relative path to the fragment shader source file with respect to the project directory.</param>
	/// <returns>True if shader is created successfully, false otherwise.</returns>
	bool CreateShader(const std::string &vsSource, const std::string& fsSource);

	/// <summary>
	/// Creates locations for point light related uniforms.
	/// </summary>
	void InitPointLightLocations();

	/// <summary>
	/// Creates locations for spotlight related uniforms.
	/// </summary>
	void InitSpotlightLocations();

	/// <summary>
	/// A utility function that creates a location for an attribute with a given name.
	/// </summary>
	/// <param name="cName">Name for the attribute that will be used to access the uniform from the C++ code side.</param>
	/// <param name="shaderName">Name for the attribute that is used in the shader source.</param>
	void CreateAttributeLocation(std::string cName, std::string shaderName);

	/// <summary>
	/// A utility function that creates a location for an uniform with a given name.
	/// </summary>
	/// <param name="cName">Name for the uniform that will be used to access the uniform from the C++ code side.</param>
	/// <param name="shaderName">Name for the attribute that is used in the shader source.
	/// The "u_" prefix that is used in the shader source should be excluded from this name.</param>
	void CreateUniformLocation(std::string cName, std::string shaderName);

public:
	/// <summary>
	/// Default constructor for the ShaderProgram class. Do not use.
	/// </summary>
	ShaderProgram() {}

	/// <summary>
	/// The ShaderProgram class constructor. Creates the shader based on the source file paths.
	/// </summary>
	/// <param name="vsPath">- relative path to the vertex shader source file with respect to the project directory.</param>
	/// <param name="fsPath">- relative path to the fragment shader source file with respect to the project directory.</param>
	/// <param name="shaderType">- enum that describes type of the shader.</param>
	ShaderProgram(std::string vsPath, std::string fsPath, ShaderType shaderType)
		: m_vertexShaderPath(vsPath)
		, m_fragmentShaderPath(fsPath)
		, m_shaderType(shaderType) {
		ShaderProgram::s_shaders.insert(std::pair<ShaderType, ShaderProgram*>(shaderType, this));
	}

	/// <summary>
	/// Tells OpenGL to use the given shader program.
	/// </summary>
	void UseShader();

	/// <summary>
	/// Loads the shader program and marks it as ready.
	/// </summary>
	/// <returns>True if the shader has been loaded successfully, false otherwise.</returns>
	bool Init();

	/// <summary>
	/// Sets a given uniform to a given integer value.
	/// </summary>
	/// <param name="name">- name of the uniform.</param>
	/// <param name="x">- value that should be assigned to the given uniform.</param>
	inline void SetUniform(std::string name, int x) {
		if (!m_ready) return;
		glUniform1i(GetLocation(name), x);
		CHECK_GL_ERROR();
	}

	/// <summary>
	/// Sets a given uniform to a given floating point value.
	/// </summary>
	/// <param name="name">- name of the uniform.</param>
	/// <param name="x">- value that should be assigned to the given uniform.</param>
	inline void SetUniform(std::string name, float x) {
		if (!m_ready) return;
		glUniform1f(GetLocation(name), x);
		CHECK_GL_ERROR();
	}

	/// <summary>
	/// Sets a given uniform to a given 3D vector.
	/// </summary>
	/// <param name="name">- name of the uniform.</param>
	/// <param name="v">- 3D vector that should be assigned to the given uniform.</param>
	inline void SetUniform(std::string name, glm::vec3& v) {
		if (!m_ready) return;
		glUniform3f(GetLocation(name), v.x, v.y, v.z);
		CHECK_GL_ERROR();
	}

	/// <summary>
	/// Sets a given uniform to a given 4x4 matrix.
	/// </summary>
	/// <param name="name">- name of the uniform.</param>
	/// <param name="m">- 4x4 matrix that should be assigned to the given uniform.</param>
	inline void SetUniform(std::string name, glm::mat4x4& m) {
		if (!m_ready) return;
		glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(m));
		CHECK_GL_ERROR();
	}

	/// <summary>
	/// Enables given attribute.
	/// </summary>
	/// <param name="name">- name of the attribute that should be enabled.</param>
	inline void EnableAttrib(std::string name) {
		glEnableVertexAttribArray(GetLocation(name));
		CHECK_GL_ERROR();
	}

	/// <summary>
	/// Abstraction layer for the glVertexAttribPointer function in case that given attribute is a float.
	/// </summary>
	/// <param name="name">- name of the attribute.</param>
	/// <param name="size">- number of elements for the given attribute (for example, 3 if given attribute is a 3D position).</param>
	/// <param name="stride">- stride of the attributes in the vertex buffer in terms of number of values
	/// (for example, 8 if given buffer should contain 3D position, 3D normal vector and 2D texture coordinates).</param>
	/// <param name="offset">- offset of the given attribute in the vertex buffer in terms of number of values
	/// (for example, 3 if given attribute is a normal vector and given buffer contains a 3D position, a 3D normal vector and a 2D texture coordinate).</param>
	inline void AttribFloat(std::string name, int size, int stride, int offset) {
		glVertexAttribPointer(GetLocation(name), size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (offset * sizeof(float)));
		CHECK_GL_ERROR();
	}

	/// <summary>
	/// Returns a location for an attribute or uniform of a given name.
	/// </summary>
	/// <param name="name">- name of the attribute or uniform.</param>
	/// <returns>The location of a given attribute or uniform.</returns>
	GLint GetLocation(std::string name);

	/// <summary>
	/// Returns a pointer to the shader program of a given type.
	/// </summary>
	/// <param name="type">- an enum that describes type of the shader.</param>
	/// <returns>Pointer to the shader program.</returns>
	static ShaderProgram* GetShader(ShaderType type);
	
	/// <summary>
	/// Notifies all shaders that the camera has changed in order to use different uniforms for rendering.
	/// </summary>
	/// <param name="id">- id of the new camera, 0 if the given camera is the dynamic camera.</param>
	static void SwitchCamera(int id);

	/// <summary>
	/// Returns the index of the next camera that will be added to the scene.
	/// </summary>
	/// <returns>The index of the next camera that will be added to the scene.</returns>
	static int AddCamera();

	static int ActiveCameraId() {
		return s_activeCameraIndex;
	}

	/// <summary>
	/// Initializes uniforms that are related to point lights and spotlights.
	/// These uniforms do not include the uniforms that will be different for each different point light or spotlight.
	/// </summary>
	void InitLights() {
		UseShader();
		SetUniform("numPointLights", s_nextPointLightIndex);
		SetUniform("numSpotlights", s_nextSpotlightIndex);
	}
};

