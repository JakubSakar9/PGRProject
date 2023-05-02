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

	if (source.contains("albedoMap")) {
		AlbedoMap(source["albedoMap"]);
	}
	else {
		AlbedoMap("none");
	}

	if (source.contains("normalMap1")) {
		NormalMap1(source["normalMap1"]);
	}
	else {
		NormalMap1("none");
	}

	if (source.contains("normalMap2")) {
		NormalMap2(source["normalMap2"]);
	}
	else {
		NormalMap2("none");
	}
}

void Material::AlbedoMap(std::string filepath) {
	if (filepath == "none") {
		m_albedoMap = 0;
		return;
	}
	std::string path = std::string("textures/") + filepath + std::string(".png");
	m_albedoMap = pgr::createTexture(path);
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBindTexture(GL_TEXTURE_2D, m_albedoMap);
}

void Material::NormalMap1(std::string filepath) {
	if (filepath == "none") {
		m_normalMap1 = 0;
		return;
	}
	std::string path = std::string("textures/") + filepath + std::string(".png");
	m_normalMap1 = pgr::createTexture(path);
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBindTexture(GL_TEXTURE_2D, m_normalMap1);
}

void Material::NormalMap2(std::string filepath) {
	if (filepath == "none") {
		m_normalMap2 = 0;
		return;
	}
	std::string path = std::string("textures/") + filepath + std::string(".png");
	m_normalMap2 = pgr::createTexture(path);
	glActiveTexture(GL_TEXTURE1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBindTexture(GL_TEXTURE_2D, m_normalMap2);
}

glm::vec3 Material::Albedo() {
	return m_albedo;
}

glm::vec3 Material::Emission() {
	return m_emission;
}

float Material::Specular() {
	return m_specular;
}

float Material::Roughness() {
	return m_roughness;
}

float Material::Transmission() {
	return m_transmission;
}

GLuint Material::AlbedoMap() {
	return m_albedoMap;
}

GLuint Material::NormalMap1() {
	return m_normalMap1;
}

GLuint Material::NormalMap2() {
	return m_normalMap2;
}

void Material::ShowProperties() {
	if (ImGui::CollapsingHeader("Material Properties")) {
		ImGui::Text((std::string("Name: ") + m_name).c_str());

		float albedo[3] = { m_albedo.x, m_albedo.y, m_albedo.z };
		ImGui::ColorPicker3("Albedo", albedo);
		m_albedo = glm::vec3(albedo[0], albedo[1], albedo[2]);

		float emission[3] = { m_emission.x, m_emission.y, m_emission.z };
		ImGui::ColorPicker3("emission", emission);
		m_emission = glm::vec3(emission[0], emission[1], emission[2]);

		ImGui::SliderFloat("Specular", &m_specular, 0.0f, 1.0f);

		ImGui::SliderFloat("Roughness", &m_roughness, 0.0f, 1.0f);
		
		ImGui::SliderFloat("Transmission", &m_transmission, 0.0f, 1.0f);
	}
}
