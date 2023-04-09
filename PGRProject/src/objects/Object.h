#pragma once

#include <string>

#include "pgr.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../ShaderType.h"
#include "../ShaderProgram.h"
#include "../WavefrontObject.h"
#include "../BoxCollider.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define VERTEX_SIZE 8
#define DEFAULT_WAVEFRONT_SCALE 0.02f
#define OBJECT_PATH_PREFIX "models/"

class ObjectInstance {

protected:
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::quat m_rotation;
	glm::mat4 m_localModelMatrix;
	glm::mat4 m_globalModelMatrix;
	
	ShaderType m_shaderType;
	BoxCollider *m_collider = nullptr;
	
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
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix, glm::vec3 cameraPos);

	/// calls draw on child nodes
	virtual void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	virtual bool GenObjects(ShaderType shaderType);
	
	void Translate(glm::vec3 delta);

	void Scale(glm::vec3 scale);

	void AddCollider(glm::vec3 &size);

	void UpdateColliders(std::vector<BoxCollider *>& colliders);
};
