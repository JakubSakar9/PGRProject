#pragma once

#include "Object.h"

#define NUM_FRAMES 4
#define NUM_KEYFRAMES 6

const float animTimes[] = {
	0.75f,
	0.05f,
	0.05f,
	0.05f,
	0.05f,
	0.05f
};

const int animFrames[] = {
	0,
	1,
	2,
	3,
	2,
	1
};

class EyeObject
	: public ObjectInstance
{
protected:
	typedef struct _ObjectGeometry {
		GLuint vertexBufferObject;
		GLuint elementBufferObject;
		GLuint vertexArrayObject;

		unsigned int numTriangles;
		unsigned int numVertices;

		std::vector<unsigned int> indices;
		std::vector<float> verticesData;
	} ObjectGeometry;

	glm::vec3 m_cameraPosition;

	ObjectGeometry m_geometry;
	Material* m_material;

	float m_animTime;
	int m_frameId;

public:
	EyeObject() {}

	EyeObject(nlohmann::json source);

	/** recalculates global matrix and updates all children
	*
	* Derived classes should also call this method (using SceneNode::update()).
	*/
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// calls draw on child nodes
	void Draw();

	bool GenObjects(std::vector<ObjectInstance *>& transparentObjects);

	void InitTextures(ShaderProgram* shaderProgram);

	void ShowProperties() override;
};

