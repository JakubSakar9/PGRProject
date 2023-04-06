#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation) {
	m_Position = position;
	m_Color = color;
	m_Intensity = intensity;
	m_attenuation = attenuation;
	m_id = ShaderProgram::s_nextPointLightIndex++;
}

void PointLight::Update(ShaderProgram* shaderProgram) {
	shaderProgram->UseShader();
	shaderProgram->SetUniform(PL("color", m_id), m_Color);
	shaderProgram->SetUniform(PL("attenuation", m_id), m_attenuation);
	shaderProgram->SetUniform(PL("intensity", m_id), m_Intensity);
	ShaderProgram::s_pointLightPositions[m_id] = m_Position;
	CHECK_GL_ERROR();
}
