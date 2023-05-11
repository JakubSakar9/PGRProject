#pragma once

#include "Object.h"

/// <summary>
/// Class for an object that represents water in the scene. This object has a material with two normal maps, which are animated. Its geometry simple geometry is generated procedurally, so there is no mesh that needs to be loaded.
/// </summary>
class Water
	: public ObjectInstance
{
protected:
	/// <summary>
	/// A struct that describes geometry of the mesh that represents the static water.
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

	/// <summary>
	/// Parameter for the procedural mesh. Describes how many quads a single strip of the water mesh contains. The number of total quads for the mesh is square of this value.
	/// </summary>
	int m_density;

	/// <summary>
	/// Describes the speed of the normal map animation.
	/// </summary>
	float m_waveSpeed;

	/// <summary>
	/// Parameter for the procedural mesh. Describes physical size of the sea and could be considered a scalar version of scale.
	/// However, unlike scale this value is only used to generate the mesh and affects positions of individual vertices in model coordinates.
	/// Changing this value during runtime will not affect the object anymore.
	/// </summary>
	float m_size;

	/// <summary>
	/// A helper attribute that holds the elapsed time in milliseconds from since the water object has been added to the scene.
	/// </summary>
	float m_time;

public:
	/// <summary>
	/// Default constructor for the Water class. Do not use.
	/// </summary>
	Water() {}

	/// <summary>
	/// The Water class constructor. Used to load the water object from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the water object data.</param>
	Water(nlohmann::json source);

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
	/// <param name="shaderProgram">- pointer to a shader program that the water object uses for rendering.</param>
	void InitTextures(ShaderProgram* shaderProgram);

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	void ShowProperties() override;
};

