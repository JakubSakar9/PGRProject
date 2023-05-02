#pragma once

#include "Object.h"

class StaticObject :
    public ObjectInstance
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
public:
	StaticObject() {}
	StaticObject(nlohmann::json source);
	~StaticObject();

	/** recalculates global matrix and updates all children
	*
	* Derived classes should also call this method (using SceneNode::update()).
	*/
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// calls draw on child nodes
	virtual void Draw();

	virtual bool GenObjects(std::vector<ObjectInstance *>& transparentObjects);

	virtual void InitTextures(ShaderProgram *shaderProgram);

	virtual void ShowProperties();
};

