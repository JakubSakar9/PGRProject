//----------------------------------------------------------------------------------------
/**
 * \file       MeshData.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <vector>

#include "pgr.h"

#define VERTEX_SIZE 8

/// <summary>
/// A struct that is used as an utility for importing mesh data using assimp.
/// </summary>
struct MeshData
{
	/// <summary>
	/// Number of vertices that the mesh contains. This includes rendundant vertices.
	/// </summary>
	int numVertices;
	
	int numFaces;

	/// <summary>
	/// Contains individual vertices in the mesh stored as 3D vectors.
	/// The vertices that have different properties for each face are stored multiple times.
	/// </summary>
	std::vector<glm::vec3> vertices;

	/// <summary>
	/// Contains normal vectors for each vertex in the mesh
	/// </summary>
	std::vector<glm::vec3> normals;

	/// <summary>
	/// Contains texture coordinates for each vertex in the mesh
	/// </summary>
	std::vector<glm::vec2> texCoords;

	/// <summary>
	/// Contains indices of the mesh faces
	/// All faces in the mesh are triangles, so each face is represented with three subsequent indicies.
	/// Note that these indices are not grouped together, much like indices in an element buffer.
	/// </summary>
	std::vector<glm::ivec3> faces;
};