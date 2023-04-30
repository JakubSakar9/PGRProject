#pragma once

#include <string>

#include "../utils/json.hpp"
#include "pgr.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../BoxCollider.h"
#include "../ResourceManager.h"
#include "../ShaderType.h"
#include "../ShaderProgram.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define DEFAULT_WAVEFRONT_SCALE 0.02f
#define OBJECT_PATH_PREFIX "models/"

class ObjectInstance {

protected:
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::quat m_rotation;
	glm::quat m_globalRotation;
	glm::mat4 m_localModelMatrix;
	glm::mat4 m_globalModelMatrix;

	std::string m_name;
	
	ShaderType m_shaderType;
	BoxCollider *m_collider = nullptr;
	
	typedef std::vector<ObjectInstance*> ObjectList;
	ObjectList m_children;

	virtual glm::mat4 ComputeModelMatrix();

	void InitTransform(nlohmann::json source);

public:
	ObjectInstance() {}
	~ObjectInstance() {}

	/** recalculates global matrix and updates all children
	*
	* Derived classes should also call this method (using SceneNode::update()).
	*/
	virtual void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// calls draw on child nodes
	virtual void Draw();

	virtual bool GenObjects();
	
	void Translate(glm::vec3 delta);

	void Scale(glm::vec3 scale);

	void AddCollider(glm::vec3 &size);

	void UpdateColliders(std::vector<BoxCollider*>& colliders);
};
