//----------------------------------------------------------------------------------------
/**
 * \file       EyeObject.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Object.h"

#define NUM_FRAMES 4
#define NUM_KEYFRAMES 6

/// <summary>
/// Predefined times of individual keyframes of the eye animation.
/// </summary>
const float animTimes[] = {
	0.75f,
	0.05f,
	0.05f,
	0.05f,
	0.05f,
	0.05f
};

/// <summary>
/// Predefined numbers of frames used for individual keyframes of the eye animation.
/// </summary>
const int animFrames[] = {
	0,
	1,
	2,
	3,
	2,
	1
};

/// <summary>
/// An object class that is specifically used for eyes for the Link character. It is the only type of object that supports frame-based animation of a texture.
/// </summary>
class EyeObject
	: public ObjectInstance
{
protected:
	/// <summary>
	/// A struct that describes geometry of the mesh that represents the eye object.
	/// </summary>
	typedef struct _ObjectGeometry {
		GLuint vertexBufferObject;
		GLuint elementBufferObject;
		GLuint vertexArrayObject;

		unsigned int numTriangles;
		unsigned int numVertices;

		std::vector<unsigned int> indices;
		std::vector<float> verticesData;
	} ObjectGeometry;

	ObjectGeometry m_geometry;

	Material* m_material;

	/// <summary>
	/// A helper attribute that holds the elapsed time in milliseconds from since the animation started.
	/// </summary>
	float m_animTime;
	
	/// <summary>
	/// A helper attribute that keeps track of number of the current frame in the eye animation.
	/// </summary>
	int m_frameId;

public:
	/// <summary>
	/// Default constructor for the EyeObject class. Do not use.
	/// </summary>
	EyeObject() {}

	/// <summary>
	/// The EyeObject class constructor. Used to load the eye object from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the eye object data.</param>
	EyeObject(nlohmann::json source);

	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
	/// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// <summary>
	/// Calls draw on all children of the given ObjectInstance. If the given object represents any geometry, it is drawn on the screen using an OpenGL draw call.
	/// </summary>
	void Draw();
	
	/// <summary>
	/// Generates all neccessary OpenGL objects. Checks child objects for any transparent objects. If any transparent objects are found, they are stored into the <paramref name="transparentObjects"></paramref> list.
	/// </summary>
	/// <param name="transparentObjects">- vector with pointers to all objects that are marked as transparent.</param>
	/// <returns>false if any errors were encountered, true otherwise.</returns>
	bool GenObjects(std::vector<ObjectInstance *>& transparentObjects);

	/// <summary>
	/// Class that is used to set all uniforms that are related to textures to correct values.
	/// </summary>
	/// <param name="shaderProgram">- pointer to a shader program that the eye object uses for rendering.</param>
	void InitTextures(ShaderProgram* shaderProgram);


	/// <summary>
	/// Generates ImGui objects that will display properties of the object.
	/// </summary>
	void ShowProperties() override;
};

