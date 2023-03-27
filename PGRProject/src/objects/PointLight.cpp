#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation) {
	m_Position = position;
	m_Color = color;
	m_Intensity = intensity;
	m_Attenuation.constant = attenuation.x;
	m_Attenuation.linear = attenuation.y;
	m_Attenuation.quadratic = attenuation.z;
}

void PointLight::Update(ShaderProgram* shaderProgram) {
	
}
