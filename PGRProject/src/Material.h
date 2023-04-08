#include <iostream>
#include <string>

#include "pgr.h"

#pragma once
class Material {
private:
	std::string m_Name;

	glm::vec3 m_Ambient;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
	glm::vec3 m_Transmission;

	GLuint m_AmbientMap;
	GLuint m_DiffuseMap;
	GLuint m_SpecularMap;
	GLuint m_DissolveMap;
	GLuint m_LightnessMap;

	int m_IlluminationModel;
	float m_DissolveFactor;
	float m_SpecularExponent;
	float m_Sharpness;
	float m_IndexOfRefraction;
	bool m_DissolveHalo;
	bool m_Antialiased;
public:
	Material(std::string name);

	Material(aiMaterial* material, const std::string& assetsDirectory);

	void Ambient(float r, float g, float b);
	void Diffuse(float r, float g, float b);
	void Specular(float r, float g, float b);
	void Transmission(float r, float g, float b);
	void IlluminationModel(int id);
	void Dissolve(float factor, bool halo);
	void SpecularExponent(float exponent);
	void Sharpness(float value);
	void IOR(float ior);
	void AmbientMap(std::string filepath);
	void DiffuseMap(std::string filepath);
	void SpecularMap(std::string filepath);
	void DissolveMap(std::string filepath);
	void LightnessMap(std::string filepath);

	glm::vec3 Diffuse();
	glm::vec3 Specular();
	float SpecularExponent();
	float DissolveFactor();
	GLuint DiffuseMap();
};