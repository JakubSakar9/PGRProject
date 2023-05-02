#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction) {
	m_direction = direction;
	m_color = color;
	m_intensity = intensity;
}

DirectionalLight::DirectionalLight(nlohmann::json source) {
	using json = nlohmann::json;
	json j_color = source["color"];
	m_color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	json j_direction = source["direction"];
	m_direction = glm::vec3(j_direction[0], j_direction[1], j_direction[2]);
	m_intensity = source["intensity"];
}

void DirectionalLight::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	for (ShaderType st : lightShaders) {
		ShaderProgram* shaderProgram = SH(st);
		glm::vec3 direction = m_rotation * m_direction;
		shaderProgram->UseShader();
		shaderProgram->SetUniform("directionalLight.color", m_color);
		shaderProgram->SetUniform("directionalLight.direction", direction);
		shaderProgram->SetUniform("directionalLight.intensity", m_intensity);
	}
}

void DirectionalLight::ShowProperties() {
	ImGui::Text("Directional Light");
	if (ImGui::CollapsingHeader("Properties")) {
		float color[3] = { m_color.x, m_color.y, m_color.z };
		ImGui::ColorPicker3("Color", color);
		m_color = glm::vec3(color[0], color[1], color[2]);

		float direction[3] = { m_direction.x, m_direction.y, m_direction.z };
		ImGui::SliderFloat3("Direction", direction, -1.0f, 1.0f);
		m_direction = glm::vec3(direction[0], direction[1], direction[2]);

		ImGui::DragFloat("Intensity", &m_intensity);
	}
}

void DirectionalLight::RenderGraph() {
	ImGui::Text("Directional Light");
	if (ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing()) {
		m_clicked = true;
	}
}
