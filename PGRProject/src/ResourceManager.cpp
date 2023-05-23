//----------------------------------------------------------------------------------------
/**
 * \file       ResourceManager.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "ResourceManager.h"
#include "objects/AmbientLight.h"

void ResourceManager::LoadAssimp(std::string filename, std::string type) {
	std::string prefix = MODEL_PREFIX + filename + std::string("/");
	std::string suffix;
	if (type == "wavefront") {
		suffix = ".obj";
	}
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(prefix + filename + suffix, ASSIMP_LOAD_FLAGS);
	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* curMesh = scene->mMeshes[i];
		MeshData* data = new MeshData();

		aiString aObjectName = curMesh->mName;
		std::string objectName(aObjectName.C_Str());

		data->numVertices = curMesh->mNumVertices;
		data->numFaces = curMesh->mNumFaces;

		for (unsigned int i = 0; i < curMesh->mNumVertices; i++) {
			const aiVector3D& position = curMesh->mVertices[i];
			const aiVector3D& normals = curMesh->mNormals[i];
			const aiVector3D& texCoords = curMesh->mTextureCoords[0][i];

			data->vertices.push_back(glm::vec3(position.x, position.y, position.z));
			data->normals.push_back(glm::vec3(normals.x, normals.y, normals.z));
			data->texCoords.push_back(glm::vec2(texCoords.x, 1 - texCoords.y));
		}

		for (int i = 0; i < curMesh->mNumFaces; i++) {
			aiFace face = curMesh->mFaces[i];
			glm::vec3 faceData = glm::vec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
			data->faces.push_back(faceData);
		}


		m_meshPool.insert(std::pair<std::string, MeshData*>(filename + objectName, data));
	}
}

void ResourceManager::LoadMaterials()
{
	using json = nlohmann::json;
	ilInit();
	std::ifstream f("data/materials.json");
	json data = json::parse(f);
	for (json j_material : data) {
		std::string matName = j_material["name"];
		m_materialPool.insert(std::pair<std::string, Material*>(
			matName, new Material(j_material)));
	}
}

MeshData* ResourceManager::GetMesh(std::string filename, std::string objectName, std::string type)
{
	std::string name = filename + objectName;
	auto it = m_meshPool.find(name);
	if (it == m_meshPool.end()) {
		LoadAssimp(filename, type);
	}
	return m_meshPool.at(name);
}

Material* ResourceManager::GetMaterial(std::string name)
{
	auto it = m_materialPool.find(name);
	if (it == m_materialPool.end()) {
		std::cerr << "ERROR: Unknown material " << name << std::endl;
		return new Material();
	}
	return m_materialPool.at(name);
}
