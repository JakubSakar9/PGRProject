#pragma once

#include <vector>

#include "pgr.h"

#define VERTEX_SIZE 8

struct MeshData
{
	int numVertices;
	int numFaces;

	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::ivec3> faces;
};