#include "ResourceManager.h"

std::vector<WavefrontObject *> ResourceManager::LoadWavefrontObj(std::string filepath)
{
	std::vector<WavefrontObject *> objects;

	std::vector<std::string*> lines;

	std::vector<WavefrontObject::Vertex *> vertices;
	std::vector<WavefrontObject::Face*> faces;
	std::vector<WavefrontObject::TexCoords*> texCoords;
	std::vector<WavefrontObject::Normal *> normals;

	std::map<std::string, Material*> groupMaterials = LoadWavefrontMtl(filepath + ".mtl");
	for (auto iter = groupMaterials.begin(); iter != groupMaterials.end(); ++iter) {
		std::cout << iter->first << std::endl;
	}
	std::map<int, Material*> objMaterials = std::map<int, Material *>();


	std::string objFilename = filepath + ".obj";
	std::ifstream in(objFilename);

	if (!in.is_open()) {
		std::cerr << "ERROR: Failed to read file " << objFilename << std::endl;
	}

	std::string line;
	while (std::getline(in, line)) {
		lines.push_back(new std::string(line));
	}
	in.close();

	int materialIndex = -1;
	int shadeSmooth;
	bool firstObject = true;
	
	WavefrontObject* currentObject;

	for (auto& line : lines) {
		std::stringstream ss(*line);
		std::string token;
		ss >> token;

		if (token == "o") {
			std::string objName;
			ss >> objName;
			currentObject = new WavefrontObject(objName);
			objects.push_back(currentObject);
		}
		else if (token == "v") {
			float x, y, z;
			ss >> x >> y >> z;
			WavefrontObject::Vertex* vertex = new WavefrontObject::Vertex(x, y, z);
			vertices.push_back(vertex);
		}
		else if (token == "f") {
			// TODO: Complete face loading
			std::vector<std::string> indices;
			std::string i1_str, i2_str, i3_str;
			ss >> i1_str >> i2_str >> i3_str;
		}
		else if (token == "vt") {
			float u, v;
			ss >> u >> v;
			WavefrontObject::TexCoords* tex = new WavefrontObject::TexCoords(u, v);
			texCoords.push_back(tex);
		}
		else if (token == "vn") {
			float x, y, z;
			ss >> x >> y >> z;
			WavefrontObject::Normal* normal = new WavefrontObject::Normal(x, y, z);
			normals.push_back(normal);
		}
		else if (token == "usemtl") {
			materialIndex++;
			std::string matName;
			ss >> matName;
			if (groupMaterials.count(matName)) {
				std::cout << materialIndex << " " << matName << std::endl;;
				objMaterials.insert(std::pair<int, Material*>(materialIndex, groupMaterials.at(matName)));
			}
		}
		else if (token == "s") {
			ss >> shadeSmooth;
		}
		delete line;
	}

	for (auto& obj : objects) {
		obj->Debug();
	}

	return objects;
}

std::map<std::string, Material*> ResourceManager::LoadWavefrontMtl(std::string filepath) {
	std::map<std::string, Material*> materials;

	std::vector<std::string*> lines;

	std::ifstream in(filepath);

	if (!in.is_open()) {
		std::cerr << "ERROR: Failed to read file " << filepath << std::endl;
	}

	std::string line;
	while (std::getline(in, line)) {
		lines.push_back(new std::string(line));
	}
	in.close();

	Material* currentMaterial = nullptr;

	for (auto& line : lines) {
		std::stringstream ss(*line);
		std::string token;
		ss >> token;

		if (token == "newmtl") {
			std::string matName;
			ss >> matName;
			currentMaterial = new Material(matName);
			materials.insert(std::pair<std::string, Material*>(matName, currentMaterial));
		}
		else if (token == "Ka") {
			float r, g, b;
			ss >> r >> g >> b;
			currentMaterial->Ambient(r, g, b);
		}
		else if (token == "Kd") {
			float r, g, b;
			ss >> r >> g >> b;
			currentMaterial->Diffuse(r, g, b);
		}
		else if (token == "Ks") {
			float r, g, b;
			ss >> r >> g >> b;
			currentMaterial->Specular(r, g, b);
		}
		else if (token == "Tf") {
			float r, g, b;
			ss >> r >> g >> b;
			currentMaterial->Transmission(r, g, b);
		}
		else if (token == "illum") {
			int id;
			ss >> id;
			currentMaterial->IlluminationModel(id);
		}
		else if (token == "d") {
		}
		else if (token == "Ns") {
		}
		else if (token == "sharpness") {
		}
		else if (token == "Ni") {
		}
		else if (token == "map_Ka") {
		}
		else if (token == "map_Kd") {
		}
		else if (token == "map_Ks") {
		}
		else if (token == "map_d") {
		}
		else if (token == "map_Ns") {
		}
		else if (token == "map_aat") {
		}
		delete line;
	}

	return materials;
}
