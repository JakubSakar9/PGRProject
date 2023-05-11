#include <iostream>
#include <string>

#include "imgui/imgui.h"
#include "utils/json.hpp"
#include "pgr.h"

#pragma once

/// <summary>
/// Class that is used to describe a material used for physically based rendering. Physically based rendering that was used is simplified and does not use BTDF.
/// </summary>
class Material {
private:
	/// <summary>
	/// Name of the material that is shown in the menu.
	/// </summary>
	std::string m_name;

	/// <summary>
	/// 3D vector that represents base color of the material. Its values should range between zero and one in order to achieve realistic results.
	/// </summary>
	glm::vec3 m_albedo;

	/// <summary>
	/// 3D vector that represents a color of the material if it is not illuminated by any light
	/// </summary>
	glm::vec3 m_emission;

	/// <summary>
	/// Base value of the specular component.
	/// </summary>
	float m_specular;

	/// <summary>
	/// A value between zero and one that affects how sharp are light reflections on the material.
	/// </summary>
	float m_roughness;

	/// <summary>
	/// A value between zero and one that describes how much light passes through the material.
	/// Zero if no light passes through the material, one if all of the light which is not reflected by specular reflection passes through the object.
	/// </summary>
	float m_transmission;

	/// <summary>
	/// OpenGL identifier for the albedo map.
	/// </summary>
	GLuint m_albedoMap;

	/// <summary>
	/// OpenGL identifier for the first normal texture, which is used for water waves
	/// </summary>
	GLuint m_normalMap1;

	/// <summary>
	/// OpenGL identifier for the second normal texture, which is used for water waves
	/// </summary>
	GLuint m_normalMap2;
public:
	/// <summary>
	/// The Material class constructor. Sets all attributes to default values.
	/// </summary>
	Material();

	/// <summary>
	/// The Material class constructor. Loads the material from the JSON object.
	/// </summary>
	/// <param name="source">- JSON object that contains data for the given material.</param>
	Material(nlohmann::json source);

	/// <summary>
	/// Loads the albedo map from a given file.
	/// </summary>
	/// <param name="filepath">Name of the albedo map file. Searches in the textures/ directory.</param>
	void AlbedoMap(std::string filepath);

	/// <summary>
	/// Loads the first normal map from a given file.
	/// </summary>
	/// <param name="filepath">Name of the first normal map file. Searches in the textures/ directory.</param>
	void NormalMap1(std::string filepath);

	/// <summary>
	/// Loads the second normal map from a given file.
	/// </summary>
	/// <param name="filepath">Name of the second normal map file. Searches in the textures/ directory.</param>
	void NormalMap2(std::string filepath);

	/// <summary>
	/// Returns albedo of the material.
	/// </summary>
	/// <returns>A 3D vector that represents albedo of the material.</returns>
	glm::vec3 Albedo();

	/// <summary>
	/// Returns emission of the material.
	/// </summary>
	/// <returns>A 3D vector that represents emission of the material.</returns>
	glm::vec3 Emission();

	/// <summary>
	/// Returns specular component of the material.
	/// </summary>
	/// <returns>A value that represents a specular component of the material.</returns>
	float Specular();

	/// <summary>
	/// Returns roughness of the material.
	/// </summary>
	/// <returns>A value that represents roughness of the material.</returns>
	float Roughness();

	/// <summary>
	/// Returns transmission of the material
	/// </summary>
	/// <returns>A value that represents transmission of the material.</returns>
	float Transmission();

	/// <summary>
	/// Returns texture object for the albedo map.
	/// </summary>
	/// <returns>An OpenGL identifier for the albedo map texture.</returns>
	GLuint AlbedoMap();

	/// <summary>
	/// Returns texture object for the first normal map.
	/// </summary>
	/// <returns>An OpenGL identifier for the first normal map texture.</returns>
	GLuint NormalMap1();

	/// <summary>
	/// Returns texture object for the second normal map.
	/// </summary>
	/// <returns>An OpenGL identifier for the second normal map texture.</returns>
	GLuint NormalMap2();

	/// <summary>
	/// Generates ImGui objects that will display properties of the object.
	/// </summary>
	void ShowProperties();
};