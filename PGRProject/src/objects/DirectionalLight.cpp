#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction) {
	m_Direction = direction;
	m_Color = color;
	m_Intensity = intensity;
}

void DirectionalLight::Update(ShaderProgram* shaderProgram) {
	glm::vec3 direction = m_rotation * m_Direction;
	shaderProgram->UseShader();
	shaderProgram->SetUniform("directionalLight.color", m_Color);
	shaderProgram->SetUniform("directionalLight.direction", direction);
	shaderProgram->SetUniform("directionalLight.intensity", m_Intensity);
}
