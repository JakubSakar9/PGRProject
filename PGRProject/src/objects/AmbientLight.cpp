#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 color, float ambientIntensity) {
	m_Color = color;
	m_Intensity = ambientIntensity;
}

AmbientLight::AmbientLight(nlohmann::json source) {
	using json = nlohmann::json;
	json j_color = source["color"];
	m_Color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	m_Intensity = source["intensity"];
}

void AmbientLight::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_DEFAULT);
	shaderProgram->UseShader();
	shaderProgram->SetUniform("ambientLight.color", m_Color);
	shaderProgram->SetUniform("ambientLight.intensity", m_Intensity);
}
