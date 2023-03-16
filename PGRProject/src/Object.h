#pragma once

#include <string>

#include "pgr.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include "ShaderType.h"
#include "ShaderProgram.h"
#include "WavefrontObject.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define VERTEX_SIZE 5
#define INDICES_COUNT 2
#define DEFAULT_WAVEFRONT_SCALE 0.02f
#define OBJECT_PATH_PREFIX "objects/"

/**
 * \brief Geometry of an object (vertices, triangles).
 */
typedef struct _ObjectGeometry {
	GLuint vertexBufferObject;						// identifier for the buffer with vertex coordinates
	GLuint elementBufferObject;				// identifier for the element buffer object
	GLuint vertexArrayObject;				// identifier for the vertex array object
	
	unsigned int numTriangles;				// number of triangles in the mesh
	unsigned int numVertices;				// number of vertices in the mesh
	unsigned int numAttributesPerVertex;	// legacy
	unsigned int numAttributes;				// legacy
	
	std::vector<unsigned int> indices;		// vertex indices stored in a vector
	std::vector<float> verticesData;		// vertex attributes stored in a vector
} ObjectGeometry;

typedef struct _ObjectTextures {
	GLuint diffuse;
} ObjectTextures;

class ObjectInstance {

protected:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::quat m_Rotation;
	glm::mat4 m_LocalModelMatrix;
	glm::mat4 m_Global_model_matrix;

	bool m_EmptyObject = false;
	
	ObjectGeometry m_Geometry;
	ObjectTextures m_Textures;
	ShaderType m_Shader_type;
	
	typedef std::vector<ObjectInstance*> ObjectList;
	ObjectList children;

	glm::mat4 ComputeModelMatrix();

public:
	ObjectInstance();
	ObjectInstance(const pgr::MeshData& meshData);
	ObjectInstance(WavefrontObject* sourceWavefront);
	ObjectInstance(const std::vector<WavefrontObject*>& sourceWavefront);
	ObjectInstance(const std::string& name, bool useAssimp, bool joinMeshes);
	ObjectInstance(aiMesh *mesh, Material *material);
	~ObjectInstance();

	/** recalculates global matrix and updates all children
	*
	* Derived classes should also call this method (using SceneNode::update()).
	*/
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix);

	/// calls draw on child nodes
	virtual void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram *shaderProgram);
	
	// TODO: Complete docs
	void UseLegacyMesh(const pgr::MeshData& meshData);

	// TODO: Complete docs
	bool GenObjects(ShaderProgram *shaderProgram);

	void LoadAssimp(const std::string& filepath, bool joinMeshes);

	void LoadCustom(const std::string& filepath, bool joinMeshes);
};
