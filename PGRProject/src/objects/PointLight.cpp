#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation) {
	m_Position = position;
	m_Color = color;
	m_Intensity = intensity;
	m_Attenuation = attenuation;
	m_Id = ShaderProgram::s_nextPointLightIndex++;
}

void PointLight::Update(ShaderProgram* shaderProgram) {
	glUniform3f(shaderProgram->locations.pointLights[m_Id].color, m_Color.x, m_Color.y, m_Color.z);
	CHECK_GL_ERROR();
	glUniform3f(shaderProgram->locations.pointLights[m_Id].attenuation, m_Attenuation.x, m_Attenuation.y, m_Attenuation.z);
	CHECK_GL_ERROR();
	glUniform1f(shaderProgram->locations.pointLights[m_Id].intensity, m_Intensity);
	CHECK_GL_ERROR();
	ShaderProgram::s_pointLightPositions[m_Id] = m_Position;
	CHECK_GL_ERROR();
}
