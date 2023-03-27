#pragma once
#include "Object.h"
class StaticObject :
    public ObjectInstance
{
private:
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

	glm::vec3 m_LocalCameraPosition;

	ObjectGeometry m_Geometry;
	Material* m_Material;
public:
	StaticObject() {}
	StaticObject(const pgr::MeshData& meshData);
	StaticObject(WavefrontObject* sourceWavefront);
	StaticObject(const std::vector<WavefrontObject*>& sourceWavefront);
	StaticObject(const std::string& name, bool useAssimp);
	StaticObject(aiMesh* mesh, Material* material);
	~StaticObject();

	void UseLegacyMesh(const pgr::MeshData& meshData);

	/** recalculates global matrix and updates all children
	*
	* Derived classes should also call this method (using SceneNode::update()).
	*/
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, glm::vec3 cameraPos);

	/// calls draw on child nodes
	void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram* shaderProgram);

	bool GenObjects(ShaderProgram* shaderProgram);

	void LoadAssimp(const std::string& filepath);

	void LoadCustom(const std::string& filepath);

	void UpdateLocalCameraPosition(glm::vec3 cameraPos);
};

