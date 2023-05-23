//----------------------------------------------------------------------------------------
/**
 * \file       Object.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <string>

#include "../imgui/imgui.h"
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
	/// <summary>
	/// A 3D vector that describes the position in local coordinate space.
	/// </summary>
	glm::vec3 m_position;

	/// <summary>
	/// A 3D vector that describes the scale in local coordinate space.
	/// </summary>
	glm::vec3 m_scale;

	/// <summary>
	/// A quaternion that describes the rotation relative to the parent object.
	/// </summary>
	glm::quat m_rotation;

	/// <summary>
	/// A quaternion that describes the rotation relative to the world.
	/// </summary>
	glm::quat m_globalRotation;

	/// <summary>
	/// A 4x4 matrix that describes the transformation from model coordinates to local coordinates of the parent object.
	/// </summary>
	glm::mat4 m_localModelMatrix;

	/// <summary>
	/// A 4x4 matrix that describes the transformation
	/// </summary>
	glm::mat4 m_globalModelMatrix;

	/// <summary>
	/// Name of the object that will be displayed in the scene graph
	/// </summary>
	std::string m_name;

	/// <summary>
	/// A utility flag that is marked as true if the given object has just been clicked in the scene graph.
	/// </summary>
	bool m_clicked = false;
	
	/// <summary>
	/// An enum that describes which shader will be used to render the object, if it is rendered.
	/// </summary>
	ShaderType m_shaderType;

	/// <summary>
	/// Pointer to the box collider of the given object. If set to nullptr, the given object has no collider.
	/// </summary>
	BoxCollider *m_collider = nullptr;
	
	typedef std::vector<ObjectInstance*> ObjectList;
	/// <summary>
	/// Contains all children of the given object. These children will be transformed in the local coordinate system of the current object. They will also be shown deeper in the scene graph than the current object.
	/// </summary>
	ObjectList m_children;

	/// <summary>
	/// Function that computes a matrix that transforms given object from its model coordinates to the local coordinate system of its parent.
	/// </summary>
	/// <returns>A 4x4 matrix which represents the transformation.</returns>
	virtual glm::mat4 ComputeModelMatrix();

	/// <summary>
	/// Loads several properties that most objects have in common from a JSON file. These properties include position, rotation, scale, name and a collider.
	/// Out of these properties, collider is the only one that may not be defined and therefore set to nullptr.
	/// </summary>
	/// <param name="source">- JSON object that contains the object data.</param>
	void InitTransform(nlohmann::json source);

public:
	/// <summary>
	/// A 3D vector that represents the position of given object in global coordinate system.
	/// </summary>
	glm::vec3 m_globalPosition = glm::vec3(0.0f);

	/// <summary>
	/// A utility flag, that determines if given object is transparent and should be rendered in second pass.
	/// </summary>
	bool m_transparent = false;

	/// <summary>
	/// Default constructor for the ObjectInstance class. Do not use.
	/// </summary>
	ObjectInstance() {}

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
	virtual bool GenObjects(std::vector<ObjectInstance*> &transparentObjects);
	
	/// <summary>
	/// Translates the object by the <paramref name="delta"></paramref> vector in the local coordinate space.
	/// </summary>
	/// <param name="delta">- vector that describes the translation transformation.</param>
	void Translate(glm::vec3 delta);

	/// <summary>
	/// Translates the object by the <paramref name="scale"></paramref> vector in the local coordinate space.
	/// </summary>
	/// <param name="scale">- vector that describes the scale transformation.</param>
	void Scale(glm::vec3 scale);

	/// <summary>
	/// Checks the object tree of the given object and adds a reference to each collider to the <paramref name="colliders"></paramref> list.
	/// </summary>
	/// <param name="colliders"></param>
	void UpdateColliders(std::vector<BoxCollider*>& colliders);

	/// <summary>
	/// Renders nodes for the current object and all of its children into the scene graph.
	/// </summary>
	virtual void RenderGraph();

	/// <summary>
	/// Iterates through all children of the given object. If one of these objects has the clicked flag set to true, this flag is set back to false and pointer to that object is returned.
	/// </summary>
	/// <returns>A pointer to the selected object.</returns>
	ObjectInstance *SelectObject();

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	virtual void ShowProperties();
};
