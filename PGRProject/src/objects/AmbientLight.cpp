#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 color, float ambientIntensity) {
	m_Color = color;
	m_Intensity = ambientIntensity;
}

void AmbientLight::Update(float deltaTime) {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_DEFAULT);
	shaderProgram->UseShader();
	shaderProgram->SetUniform("ambientLight.color", m_Color);
	shaderProgram->SetUniform("ambientLight.intensity", m_Intensity);
}
