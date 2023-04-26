#include "Spotlight.h"



Spotlight::Spotlight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation, glm::vec3 direction, float size) {
	m_position = position;
	m_Color = color;
	m_Intensity = intensity;
	m_attenuation = attenuation;
	m_direction = direction;
	m_sizeDegrees = size;
	m_id = ShaderProgram::s_nextSpotlightIndex++;
}

Spotlight::Spotlight(nlohmann::json source) {
	InitTransform(source);

	using json = nlohmann::json;
	json j_color = source["color"];
	m_Color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	m_Intensity = source["intensity"];
	json j_attenuation = source["attenuation"];
	m_attenuation = glm::vec3(j_attenuation[0], j_attenuation[1], j_attenuation[2]);
	json j_direction = source["direction"];
	m_direction = glm::vec3(j_direction[0], j_direction[1], j_direction[2]);
	m_sizeDegrees = source["size"];
	m_id = ShaderProgram::s_nextSpotlightIndex++;
}

void Spotlight::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	for (ShaderType st : lightShaders) {
		ShaderProgram* shaderProgram = SH(st);
		shaderProgram->UseShader();
		shaderProgram->SetUniform(SL("position", m_id), m_position);
		shaderProgram->SetUniform(SL("color", m_id), m_Color);
		shaderProgram->SetUniform(SL("attenuation", m_id), m_attenuation);
		shaderProgram->SetUniform(SL("intensity", m_id), m_Intensity);
		shaderProgram->SetUniform(SL("direction", m_id), m_direction);
		shaderProgram->SetUniform(SL("size", m_id), glm::radians(m_sizeDegrees));
		CHECK_GL_ERROR();
	}
}