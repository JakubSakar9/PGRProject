#include "Material.h"

Material::Material() {
	m_name = "default";
	m_albedo = glm::vec3(0.8f);
	m_emission = glm::vec3(0.0f);
	m_specular = 0.0f;
	m_roughness = 1.0;
	m_transmission = 0.0f;

	m_albedoMap = 0;
}

Material::Material(nlohmann::json source) {
	using json = nlohmann::json;
	std::string nameTemp = source["name"];
	m_name = nameTemp;
	json j_albedo = source["albedo"];
	m_albedo = glm::vec3(j_albedo[0], j_albedo[1], j_albedo[2]);
	json j_emission = source["emission"];
	m_emission = glm::vec3(j_emission[0], j_emission[1], j_emission[2]);
	m_specular = source["specular"];
	m_roughness = source["roughness"];
	m_transmission = source["transmission"];

	AlbedoMap(source["albedoMap"]);
}

void Material::AlbedoMap(std::string filepath) {
	if (filepath == "none") {
		m_albedoMap = 0;
		return;
	}
	//m_albedoMap = pgr::createTexture("models/link/body.png");
	std::string albedoPath = std::string("textures/") + filepath + std::string(".png");
	m_albedoMap = pgr::createTexture(albedoPath);
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBindTexture(GL_TEXTURE_2D, m_albedoMap);
}

glm::vec3 Material::Albedo()
{
	return m_albedo;
}

glm::vec3 Material::Emission()
{
	return m_emission;
}

float Material::Specular()
{
	return m_specular;
}

float Material::Roughness()
{
	return m_roughness;
}

float Material::Transmission()
{
	return m_transmission;
}

GLuint Material::AlbedoMap()
{
	return m_albedoMap;
}
