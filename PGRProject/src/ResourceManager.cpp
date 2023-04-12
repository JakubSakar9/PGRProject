#include "ResourceManager.h"
#include "objects/AmbientLight.h"

//std::vector<WavefrontObject *> ResourceManager::LoadWavefrontObj(std::string filepath)
//{
//	std::vector<WavefrontObject *> objects;
//
//	std::vector<std::string*> lines;
//
//	std::vector<WavefrontObject::Vertex *> vertices;
//	std::vector<WavefrontObject::Face*> faces;
//	std::vector<WavefrontObject::TexCoords*> texCoords;
//	std::vector<WavefrontObject::Normal *> normals;
//
//	std::map<std::string, Material*> groupMaterials = LoadWavefrontMtl(filepath + ".mtl");
//	for (auto iter = groupMaterials.begin(); iter != groupMaterials.end(); ++iter) {
//		std::cout << iter->first << std::endl;
//	}
//	std::map<int, Material*> objMaterials = std::map<int, Material *>();
//
//
//	std::string objFilename = filepath + ".obj";
//	std::ifstream in(objFilename);
//
//	if (!in.is_open()) {
//		std::cerr << "ERROR: Failed to read file " << objFilename << std::endl;
//	}
//
//	std::string line;
//	while (std::getline(in, line)) {
//		lines.push_back(new std::string(line));
//	}
//	in.close();
//
//	int materialIndex = -1;
//	int shadeSmooth;
//	bool firstObject = true;
//	
//	WavefrontObject* currentObject;
//
//	for (auto& line : lines) {
//		std::stringstream ss(*line);
//		std::string token;
//		ss >> token;
//
//		if (token == "o") {
//			std::string objName;
//			ss >> objName;
//			currentObject = new WavefrontObject(objName);
//			objects.push_back(currentObject);
//		}
//		else if (token == "v") {
//			float x, y, z;
//			ss >> x >> y >> z;
//			WavefrontObject::Vertex* vertex = new WavefrontObject::Vertex(x, y, z);
//			vertices.push_back(vertex);
//		}
//		else if (token == "f") {
//			// TODO: Complete face loading
//			std::vector<std::string> indices;
//			std::string i1_str, i2_str, i3_str;
//			ss >> i1_str >> i2_str >> i3_str;
//		}
//		else if (token == "vt") {
//			float u, v;
//			ss >> u >> v;
//			WavefrontObject::TexCoords* tex = new WavefrontObject::TexCoords(u, v);
//			texCoords.push_back(tex);
//		}
//		else if (token == "vn") {
//			float x, y, z;
//			ss >> x >> y >> z;
//			WavefrontObject::Normal* normal = new WavefrontObject::Normal(x, y, z);
//			normals.push_back(normal);
//		}
//		else if (token == "usemtl") {
//			materialIndex++;
//			std::string matName;
//			ss >> matName;
//			if (groupMaterials.count(matName)) {
//				std::cout << materialIndex << " " << matName << std::endl;;
//				objMaterials.insert(std::pair<int, Material*>(materialIndex, groupMaterials.at(matName)));
//			}
//		}
//		else if (token == "s") {
//			ss >> shadeSmooth;
//		}
//		delete line;
//	}
//
//	for (auto& obj : objects) {
//		obj->Debug();
//	}
//
//	return objects;
//}

void ResourceManager::LoadAssimp(std::string filename, std::string type) {
	std::string prefix = MODEL_PREFIX + filename + std::string("/");
	std::string suffix;
	if (type == "wavefront") {
		suffix = ".obj";
	}
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(prefix + filename + suffix, ASSIMP_LOAD_FLAGS);
	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh *curMesh = scene->mMeshes[i];
		aiString aObjectName = curMesh->mName;
		std::string objectName(aObjectName.C_Str());
		m_meshPool.insert(std::pair<std::string, aiMesh*>(filename + objectName, curMesh));
	}
}

void ResourceManager::LoadJson(std::string name) {
	using json = nlohmann::json;
	std::ifstream f("misc/test.json");
	json data = json::parse(f);
	AmbientLight ambientLight(data["ambientLight"]);
}

aiMesh* ResourceManager::GetMesh(std::string filename, std::string objectName, std::string type)
{
	std::string name = filename + objectName;
	auto it = m_meshPool.find(name);
	if (it == m_meshPool.end()) {
		LoadAssimp(filename, objectName);
	}
	return m_meshPool.at(name);
}
