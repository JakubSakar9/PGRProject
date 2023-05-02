#pragma once

#include "Object.h"

class Water
	: public ObjectInstance
{
protected:
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
	int m_density;
	float m_waveSpeed;
	float m_size;

	float m_time;

public:
	Water() {}
	Water(nlohmann::json source);
	~Water();

	/** recalculates global matrix and updates all children
	*
	* Derived classes should also call this method (using SceneNode::update()).
	*/
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	void Draw();

	bool GenObjects(std::vector<ObjectInstance *>& transparentObjects);

	void InitTextures(ShaderProgram* shaderProgram);

	void ShowProperties() override;
};

