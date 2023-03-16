#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "pgr.h"

#include "Material.h"

class WavefrontObject
{
public:
	typedef struct _Face {
		int faceID;
		int vertices[3];
		int shadeSmooth;

		_Face(int id, int v1, int v2, int v3, int smooth)
			: faceID(faceID), shadeSmooth(smooth) {
			vertices[0] = v1;
			vertices[1] = v2;
			vertices[2] = v3;
		}
	} Face;

	typedef glm::vec3 Vertex;
	typedef glm::vec3 Normal;
	typedef glm::vec2 TexCoords;
private:
	std::string m_Name;
	std::vector<Vertex*> m_Vertices;
	std::vector<Normal*> m_Normals;
	std::vector<TexCoords*> m_TexCoords;
	std::vector<Face*> m_Faces;

	int state_SmoothShading;
	
	Material *m_Material;
public:
	WavefrontObject(std::string name)
		: m_Name(name)
	{
		m_Vertices = std::vector<Vertex*>();
		m_Normals = std::vector<Normal*>();
		m_TexCoords = std::vector<TexCoords*>();
		m_Faces = std::vector<Face*>();
	}

	inline void Debug() {
		std::cout << m_Name << "(" << m_Vertices.size() << ", " << m_TexCoords.size() << ")" << std::endl;
	}

	void AddVertex(float x, float y, float z);
	void AddNormal(float x, float y, float z);
	void AddTexCoords(float u, float v);
	void AddFace(int v1, int v2, int v3);
};

