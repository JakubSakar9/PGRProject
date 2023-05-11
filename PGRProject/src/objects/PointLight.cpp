#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation) {
	m_position = position;
	m_color = color;
	m_intensity = intensity;
	m_attenuation = attenuation;
	m_id = ShaderProgram::s_nextPointLightIndex++;
}

PointLight::PointLight(nlohmann::json source) {
	InitTransform(source);

	using json = nlohmann::json;
	json j_color = source["color"];
	m_color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	m_intensity = source["intensity"];
	json j_attenuation = source["attenuation"];
	m_attenuation = glm::vec3(j_attenuation[0], j_attenuation[1], j_attenuation[2]);
	m_pulseFrequency = source["pulseFrequency"];
	m_pulseSmoothness = source["pulseSmoothness"];
	m_id = ShaderProgram::s_nextPointLightIndex++;
}

void PointLight::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	m_time += deltaTime;
	if (m_pulseSmoothness < 1.0f) {
		m_pulseSmoothness = 1.0f;
	}
	float effectiveIntensity = (glm::cos(2.0f * m_time * glm::pi<float>() * m_pulseFrequency) + m_pulseSmoothness) * m_intensity / (m_pulseSmoothness + 1.0f);
	for (ShaderType st : lightShaders) {
		ShaderProgram* shaderProgram = SH(st);
		shaderProgram->UseShader();
		shaderProgram->SetUniform(PL("position", m_id), m_position);
		shaderProgram->SetUniform(PL("color", m_id), m_color);
		shaderProgram->SetUniform(PL("attenuation", m_id), m_attenuation);
		shaderProgram->SetUniform(PL("intensity", m_id), effectiveIntensity);
		CHECK_GL_ERROR();
	}
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
}

void PointLight::ShowProperties() {
	ObjectInstance::ShowProperties();
	if (ImGui::CollapsingHeader("Properties")) {
		float color[3] = { m_color.x, m_color.y, m_color.z };
		ImGui::ColorPicker3("Color", color);
		m_color = glm::vec3(color[0], color[1], color[2]);

		float attenuation[3] = { m_attenuation.x, m_attenuation.y, m_attenuation.z };
		ImGui::SliderFloat3("Attenuation", attenuation, 0.0f, 1.0f);
		m_attenuation = glm::vec3(attenuation[0], attenuation[1], attenuation[2]);

		ImGui::SliderFloat("Intensity", &m_intensity, 0.0f, 10.0f);
	}

	if (ImGui::CollapsingHeader("Pulse")) {
		ImGui::SliderFloat("Frequency", &m_pulseFrequency, 0.0f, 1.0f);
		ImGui::SliderFloat("Smoothness", &m_pulseSmoothness, 1.0f, 16.0f);
	}
}
