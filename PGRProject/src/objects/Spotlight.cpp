#include "Spotlight.h"



Spotlight::Spotlight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation, glm::vec3 direction, float size) {
	m_position = position;
	m_color = color;
	m_intensity = intensity;
	m_attenuation = attenuation;
	m_direction = direction;
	m_sizeDegrees = size;
	m_id = ShaderProgram::s_nextSpotlightIndex++;
}

Spotlight::Spotlight(nlohmann::json source) {
	InitTransform(source);

	using json = nlohmann::json;
	json j_color = source["color"];
	m_color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	m_intensity = source["intensity"];
	json j_attenuation = source["attenuation"];
	m_attenuation = glm::vec3(j_attenuation[0], j_attenuation[1], j_attenuation[2]);
	json j_direction = source["direction"];
	m_direction = glm::vec3(j_direction[0], j_direction[1], j_direction[2]);
	m_sizeDegrees = source["size"];
	m_id = ShaderProgram::s_nextSpotlightIndex++;
}

void Spotlight::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	for (ShaderType st : lightShaders) {
		ShaderProgram* shaderProgram = SH(st);
		shaderProgram->UseShader();
		shaderProgram->SetUniform(SL("position", m_id), m_position);
		shaderProgram->SetUniform(SL("color", m_id), m_color);
		shaderProgram->SetUniform(SL("attenuation", m_id), m_attenuation);
		shaderProgram->SetUniform(SL("intensity", m_id), m_intensity);
		shaderProgram->SetUniform(SL("direction", m_id), m_direction);
		shaderProgram->SetUniform(SL("size", m_id), glm::radians(m_sizeDegrees));
		CHECK_GL_ERROR();
	}
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
}

void Spotlight::ShowProperties() {
	ObjectInstance::ShowProperties();
	if (ImGui::CollapsingHeader("Properties")) {
		float color[3] = { m_color.x, m_color.y, m_color.z };
		ImGui::ColorPicker3("Color", color);
		m_color = glm::vec3(color[0], color[1], color[2]);

		float direction[3] = { m_direction.x, m_direction.y, m_direction.z };
		ImGui::SliderFloat3("Direction", direction, -1.0f, 1.0f);
		m_direction = glm::vec3(direction[0], direction[1], direction[2]);

		float attenuation[3] = { m_attenuation.x, m_attenuation.y, m_attenuation.z };
		ImGui::SliderFloat3("Attenuation", attenuation, 0.0f, 1.0f);
		m_attenuation = glm::vec3(attenuation[0], attenuation[1], attenuation[2]);

		ImGui::DragFloat("Intensity", &m_intensity);
		ImGui::DragFloat("Size", &m_sizeDegrees);
	}
}
