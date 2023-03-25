#pragma once

#include <string>

#include "pgr.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../ShaderType.h"
#include "../ShaderProgram.h"
#include "../WavefrontObject.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define VERTEX_SIZE 5
#define INDICES_COUNT 2
#define DEFAULT_WAVEFRONT_SCALE 0.02f
#define OBJECT_PATH_PREFIX "models/"

class ObjectInstance {

protected:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::quat m_Rotation;
	glm::mat4 m_LocalModelMatrix;
	glm::mat4 m_Global_model_matrix;
	
	ShaderType m_Shader_type;
	
	typedef std::vector<ObjectInstance*> ObjectList;
	ObjectList children;

	glm::mat4 ComputeModelMatrix();

public:
	ObjectInstance() {}
	~ObjectInstance() {}

	/** recalculates global matrix and updates all children
	*
	* Derived classes should also call this method (using SceneNode::update()).
	*/
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix);

	/// calls draw on child nodes
	virtual void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram *shaderProgram);

	virtual bool GenObjects(ShaderProgram *shaderProgram);
	
	void Translate(glm::vec3 delta);
};
