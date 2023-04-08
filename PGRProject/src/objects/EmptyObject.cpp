#include "EmptyObject.h"

EmptyObject::EmptyObject(const std::vector<WavefrontObject*>& sourceWavefront) {
	// Not yet implemented
}

EmptyObject::EmptyObject(const std::string& name, bool useAssimp) {
	m_shaderType = SHADER_TYPE_DEFAULT;
	std::string sourceFilepath = OBJECT_PATH_PREFIX + name + "/" + name + ".obj";
	if (useAssimp) {
		LoadAssimp(sourceFilepath);
	}
	else {
		LoadCustom(sourceFilepath);
	}
	m_scale = glm::vec3(DEFAULT_WAVEFRONT_SCALE);
}

EmptyObject::~EmptyObject() {
	ObjectInstance::~ObjectInstance();
}

void EmptyObject::LoadAssimp(const std::string& filepath) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, ASSIMP_LOAD_FLAGS);

	std::string assetsDirectory;
	const size_t lastSlashIdx = filepath.rfind('/');
	if (std::string::npos != lastSlashIdx) {
		assetsDirectory = filepath.substr(0, lastSlashIdx) + "/";
	}

	if (!scene) {
		std::cerr << "Failed to load aiScene" << std::endl;
		return;
	}

	std::vector<Material*> materials;
	for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* importedMaterial = scene->mMaterials[i];
		Material* currentMaterial = new Material(importedMaterial, assetsDirectory);
		materials.push_back(currentMaterial);
	}


	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		ObjectInstance *newObject = new StaticObject(scene->mMeshes[i], materials[scene->mMeshes[i]->mMaterialIndex]);
		children.push_back(newObject);
	}
	std::reverse(children.begin(), children.end());
}

void EmptyObject::LoadCustom(const std::string& filepath) {
}