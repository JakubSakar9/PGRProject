#pragma once

#include <cstring>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "utils/json.hpp"

#include "WavefrontObject.h"

#define MODEL_PREFIX std::string("models/")

class ResourceManager
{
private:
	std::map<std::string, aiMesh*> m_meshPool;

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

	aiMesh *GetMesh(std::string filename, std::string objectName, std::string type);
};

