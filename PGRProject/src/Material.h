#include <iostream>
#include <string>

#include "utils/json.hpp"
#include "pgr.h"

#pragma once
class Material {
private:
	std::string m_name;

	glm::vec3 m_albedo;
	glm::vec3 m_emission;
	float m_specular;
	float m_roughness;
	float m_transmission;

	GLuint m_albedoMap;
	GLuint m_normalMap1;
	GLuint m_normalMap2;
public:
	Material();
	Material(nlohmann::json source);

	void AlbedoMap(std::string filepath);
	void NormalMap1(std::string filepath);
	void NormalMap2(std::string filepath);

	glm::vec3 Albedo();
	glm::vec3 Emission();
	float Specular();
	float Roughness();
	float Transmission();
	GLuint AlbedoMap();
	GLuint NormalMap1();
	GLuint NormalMap2();
};