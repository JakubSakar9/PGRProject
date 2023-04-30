#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction) {
	m_Direction = direction;
	m_color = color;
	m_intensity = intensity;
}

DirectionalLight::DirectionalLight(nlohmann::json source) {
	using json = nlohmann::json;
	json j_color = source["color"];
	m_color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	json j_direction = source["direction"];
	m_Direction = glm::vec3(j_direction[0], j_direction[1], j_direction[2]);
	m_intensity = source["intensity"];
}

void DirectionalLight::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	for (ShaderType st : lightShaders) {
		ShaderProgram* shaderProgram = SH(st);
		glm::vec3 direction = m_rotation * m_Direction;
		shaderProgram->UseShader();
		shaderProgram->SetUniform("directionalLight.color", m_color);
		shaderProgram->SetUniform("directionalLight.direction", direction);
		shaderProgram->SetUniform("directionalLight.intensity", m_intensity);
	}
}
