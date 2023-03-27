#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 color, float ambientIntensity) {
	m_Color = color;
	m_Intensity = ambientIntensity;
}

void AmbientLight::Update(ShaderProgram *shaderProgram) {
	auto loc = shaderProgram->locations.ambientLight;
	glUniform3f(loc.color, m_Color.x, m_Color.y, m_Color.z);
	CHECK_GL_ERROR();
	glUniform1f(loc.intensity, m_Intensity);
	CHECK_GL_ERROR();
}
