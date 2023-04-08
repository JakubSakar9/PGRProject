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

void Spotlight::Update(ShaderProgram* shaderProgram) {
	shaderProgram->UseShader();
	shaderProgram->SetUniform(SL("color", m_id), m_Color);
	shaderProgram->SetUniform(SL("attenuation", m_id), m_attenuation);
	shaderProgram->SetUniform(SL("intensity", m_id), m_Intensity);
	shaderProgram->SetUniform(SL("direction", m_id), m_direction);
	shaderProgram->SetUniform(SL("size", m_id), glm::radians(m_sizeDegrees));
	ShaderProgram::s_spotlightPositions[m_id] = m_position;
	CHECK_GL_ERROR();
}