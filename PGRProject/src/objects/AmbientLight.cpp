#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 color, float ambientIntensity) {
	m_color = color;
	m_intensity = ambientIntensity;
}

AmbientLight::AmbientLight(nlohmann::json source) {
	using json = nlohmann::json;
	json j_color = source["color"];
	m_color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	m_intensity = source["intensity"];
}

void AmbientLight::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	for (ShaderType st : lightShaders) {
		ShaderProgram* shaderProgram = SH(st);
		shaderProgram->UseShader();
		shaderProgram->SetUniform("ambientLight.color", m_color);
		shaderProgram->SetUniform("ambientLight.intensity", m_intensity);
	}
};
