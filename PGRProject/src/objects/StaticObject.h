#pragma once

#include "Object.h"

/// <summary>
/// Class that describes an object that contains a mesh that can be rendered
/// </summary>
class StaticObject :
    public ObjectInstance
{
protected:
	/// <summary>
	/// A struct that describes geometry of the mesh that represents the static object.
	/// </summary>
	typedef struct _ObjectGeometry {
		GLuint vertexBufferObject;				// identifier for the buffer with vertex coordinates
		GLuint elementBufferObject;				// identifier for the element buffer object
		GLuint vertexArrayObject;				// identifier for the vertex array object

		unsigned int numTriangles;				// number of triangles in the mesh
		unsigned int numVertices;				// number of vertices in the mesh
		unsigned int numAttributesPerVertex;	// legacy
		unsigned int numAttributes;				// legacy

		std::vector<unsigned int> indices;		// vertex indices stored in a vector
		std::vector<float> verticesData;		// vertex attributes stored in a vector
	} ObjectGeometry;

	ObjectGeometry m_geometry;
	Material* m_material;
public:
	/// <summary>
	/// Default constructor for the StaticObject class. Do not use.
	/// </summary>
	StaticObject() {}

	/// <summary>
	/// The StaticObject class constructor. Used to load the static object from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the static object data.</param>
	StaticObject(nlohmann::json source);

	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
	/// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// <summary>
	/// Calls draw on all children of the given ObjectInstance. If the given object represents any geometry, it is drawn on the screen using an OpenGL draw call.
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// Generates all neccessary OpenGL objects. Checks child objects for any transparent objects. If any transparent objects are found, they are stored into the <paramref name="transparentObjects"></paramref> list.
	/// </summary>
	/// <param name="transparentObjects">- vector with pointers to all objects that are marked as transparent.</param>
	/// <returns>false if any errors were encountered, true otherwise.</returns>
	virtual bool GenObjects(std::vector<ObjectInstance *>& transparentObjects);

	/// <summary>
	/// Class that is used to set all uniforms that are related to textures to correct values.
	/// </summary>
	/// <param name="shaderProgram">- pointer to a shader program that the eye object uses for rendering.</param>
	virtual void InitTextures(ShaderProgram *shaderProgram);

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	virtual void ShowProperties();
};

