//----------------------------------------------------------------------------------------
/**
 * \file       ResourceManager.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

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

/// <summary>
/// A class that takes care of loading resources from files
/// </summary>
class ResourceManager
{
private:
	/// <summary>
	/// A map that contains data about individual meshes that have been loaded and uses their names as keys.
	/// </summary>
	std::map<std::string, MeshData*> m_meshPool;

	/// <summary>
	/// A map that contains data about individual materials that have been loaded and uses their names as keys.
	/// </summary>
	std::map<std::string, Material*> m_materialPool;

	/// <summary>
	/// Default constructor for the ResourceManager classer.
	/// </summary>
	ResourceManager() {}

	/// <summary>
	/// Loads a 3D mesh using the Assimp library.
	/// </summary>
	/// <param name="filename">- filename for the source object file. File extension is not included.</param>
	/// <param name="type">- type of the source file for the mesh. Currently, only "wavefront" is supported.</param>
	void LoadAssimp(std::string filename, std::string type);
public:
	ResourceManager(const ResourceManager&) = delete;

	/// <summary>
	/// Getter for the singleton instance of the ResourceManager class.
	/// </summary>
	/// <returns>A resource manager instance.</returns>
	static ResourceManager& Get() {
		static ResourceManager s_instance;
		return s_instance;
	}

	/// <summary>
	/// Loads materials from a JSON file. In order to work appropriate JSON file needs to be in the data/ folder.
	/// </summary>
	void LoadMaterials();

	/// <summary>
	/// Retrieves mesh data from the mesh pool or loads the mesh if it is not in the mesh pool yet.
	/// </summary>
	/// <param name="filename">- filename for the source object file. File extension is not included.</param>
	/// <param name="objectName">- name of the specific mesh that is part of the loaded object.</param>
	/// <param name="type">- type of the source file for the mesh. Currently, only "wavefront" is supported.</param>
	/// <returns>A pointer to the data of the specified mesh or nullptr if no such mesh can be loaded.</returns>
	MeshData *GetMesh(std::string filename, std::string objectName, std::string type);

	/// <summary>
	/// Retrieves material data from the material pool or loads the material if it is not in the material pool yet.
	/// </summary>
	/// <param name="name">- name of the material which is to be loaded.</param>
	/// <returns>A pointer to the specified material or nullptr if no such material can be loaded.</returns>
	Material* GetMaterial(std::string name);
};