#include "Material.h"

Material::Material(std::string name) {
	m_Name = name;
	m_Ambient = glm::vec3();
	m_Diffuse = glm::vec3();
	m_Specular = glm::vec3();
	m_Transmission = glm::vec3(0.0f);
	m_IlluminationModel = 0;
	m_DissolveFactor = 0.0f;
	m_DissolveHalo = false;
}

Material::Material(aiMaterial* sourceMaterial, const std::string& assetsDirectory) {
	m_DiffuseMap = 0;
	if (sourceMaterial->GetTextureCount(aiTextureType_DIFFUSE) >= 1) {
		aiString sourceDiffusePath;
		if (sourceMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &sourceDiffusePath, nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) {
			std::string diffusePath(assetsDirectory + sourceDiffusePath.data);
			if (diffusePath.find("eye_anim") != std::string::npos) {
				m_eye = true;
			}
			else {
				m_eye = false;
			}
			DiffuseMap(diffusePath);
		}
		
	}
	aiColor3D diffuseColor;
	sourceMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
	Diffuse(diffuseColor.r, diffuseColor.g, diffuseColor.b);

	aiColor3D specularColor;
	sourceMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
	Specular(specularColor.r, specularColor.g, specularColor.b);

	aiGetMaterialFloat(sourceMaterial, AI_MATKEY_OPACITY, &m_DissolveFactor);
	m_DissolveFactor = m_DissolveFactor;
	aiGetMaterialFloat(sourceMaterial, AI_MATKEY_SHININESS, &m_SpecularExponent);
}

void Material::Ambient(float r, float g, float b) {
	m_Ambient = glm::vec3(r, g, b);
}

void Material::Diffuse(float r, float g, float b) {
	m_Diffuse = glm::vec3(r, g, b);
}

void Material::Specular(float r, float g, float b) {
	m_Specular = glm::vec3(r, g, b);
}

void Material::Transmission(float r, float g, float b) {
	m_Transmission = glm::vec3(r, g, b);
}

void Material::IlluminationModel(int id) {
	m_IlluminationModel = id;
}

void Material::Dissolve(float factor, bool halo) {
	m_DissolveFactor = factor;
	m_DissolveHalo = halo;
}

void Material::SpecularExponent(float exponent) {
	m_SpecularExponent = exponent;
}

void Material::Sharpness(float value) {
	m_Sharpness = value;
}

void Material::IOR(float ior) {
	m_IndexOfRefraction = ior;
}

void Material::AmbientMap(std::string filepath) {
	m_AmbientMap = pgr::createTexture(filepath);
}

void Material::DiffuseMap(std::string filepath) {
	if (filepath == "NONE") {
		m_DiffuseMap = 0;
		return;
	}
	m_DiffuseMap = pgr::createTexture(filepath);
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
}

void Material::SpecularMap(std::string filepath) {
	m_SpecularMap = pgr::createTexture(filepath);
}

void Material::DissolveMap(std::string filepath) {
	m_DissolveMap = pgr::createTexture(filepath);
}

void Material::LightnessMap(std::string filepath) {
}

glm::vec3 Material::Diffuse() {
	return m_Diffuse;
}

glm::vec3 Material::Specular() {
	return m_Specular;
}

float Material::SpecularExponent() {
	return m_SpecularExponent;
}

float Material::DissolveFactor()
{
	return m_DissolveFactor;
}

GLuint Material::DiffuseMap() {
	return m_DiffuseMap;
}
