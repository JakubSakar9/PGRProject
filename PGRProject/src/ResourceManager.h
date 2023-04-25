#pragma once

#include <cstring>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "utils/json.hpp"

#include "Material.h"
#include "objects/utils/MeshData.h"

#define MODEL_PREFIX std::string("models/")

class ResourceManager
{
private:
	std::map<std::string, MeshData*> m_meshPool;

	std::map<std::string, Material*> m_materialPool;

	ResourceManager() {}

	void LoadAssimp(std::string filename, std::string type);
public:
	ResourceManager(const ResourceManager&) = delete;

	static ResourceManager& Get() {
		static ResourceManager s_Instance;
		return s_Instance;
	}

	//std::vector<WavefrontObject *> LoadWavefrontObj(std::string filepath);

	void LoadJson(std::string name);

	void LoadMaterials();

	MeshData *GetMesh(std::string filename, std::string objectName, std::string type);

	Material* GetMaterial(std::string name);
};

