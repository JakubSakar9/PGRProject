#pragma once

#include <cstring>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "WavefrontObject.h"

class ResourceManager
{
private:
	ResourceManager() {}
public:
	ResourceManager(const ResourceManager&) = delete;

	static ResourceManager& Get() {
		static ResourceManager s_Instance;
		return s_Instance;
	}

	bool Init();

	std::vector<WavefrontObject *> LoadWavefrontObj(std::string filepath);

	std::map<std::string, Material*> LoadWavefrontMtl(std::string filepath);
};

