#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation) {
	m_position = position;
	m_color = color;
	m_intensity = intensity;
	m_attenuation = attenuation;
	m_id = ShaderProgram::s_nextPointLightIndex++;
}

PointLight::PointLight(nlohmann::json source) {
	InitTransform(source);

	using json = nlohmann::json;
	json j_color = source["color"];
	m_color = glm::vec3(j_color[0], j_color[1], j_color[2]);
	m_intensity = source["intensity"];
	json j_attenuation = source["attenuation"];
	m_attenuation = glm::vec3(j_attenuation[0], j_attenuation[1], j_attenuation[2]);
	m_pulsePeriod = source["pulse"];
	m_id = ShaderProgram::s_nextPointLightIndex++;
}

void PointLight::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	m_time += deltaTime;
	float effectiveIntensity = (glm::sin(m_time * glm::pi<float>() / m_pulsePeriod) + 7) * m_intensity / 8.0f;
	for (ShaderType st : lightShaders) {
		ShaderProgram* shaderProgram = SH(st);
		shaderProgram->UseShader();
		shaderProgram->SetUniform(PL("position", m_id), m_position);
		shaderProgram->SetUniform(PL("color", m_id), m_color);
		shaderProgram->SetUniform(PL("attenuation", m_id), m_attenuation);
		shaderProgram->SetUniform(PL("intensity", m_id), effectiveIntensity);
		CHECK_GL_ERROR();
	}
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
}
