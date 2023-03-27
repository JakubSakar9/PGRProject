#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction) {
	m_Direction = direction;
	m_Color = color;
	m_Intensity = intensity;
}

void DirectionalLight::Update(ShaderProgram* shaderProgram) {
	glm::vec3 direction = m_Rotation * m_Direction;
	
	auto loc = shaderProgram->locations.directionalLight;
	glUniform3f(loc.color, m_Color.x, m_Color.y, m_Color.z);
	glUniform3f(loc.direction, direction.x, direction.y, direction.z);
	glUniform1f(loc.intensity, m_Intensity);
}
