#include "Water.h"

Water::Water(nlohmann::json source) {
	InitTransform(source);
	m_shaderType = SHADER_TYPE_WATER;
	m_time = 0.0f;

	// Params: waveSpeed, density (sqrt(numQuads))
	m_density = source["density"];
	m_waveSpeed = source["waveSpeed"];
	m_size = source["size"];
	
	m_geometry.numVertices = (1 + m_density) * (1 + m_density);
	m_geometry.numTriangles = 2 * m_density * m_density;
	m_geometry.numAttributes = m_geometry.numVertices * 3;
	m_geometry.numAttributesPerVertex = 3;
	m_geometry.verticesData.reserve(m_geometry.numAttributes);
	//m_geometry.indices.reserve(2 * (m_density + 1) * m_density);
	m_geometry.indices.reserve(3 * m_geometry.numTriangles);

	for (int i = 0; i < m_density + 1; i++) {
		for (int j = 0; j < m_density + 1; j++) {
			m_geometry.verticesData.push_back(2 * m_size * i / m_density - m_size);
			m_geometry.verticesData.push_back(0.05f);
			m_geometry.verticesData.push_back(2 * m_size * j / m_density - m_size);
		}
	}

	/*for (int i = 0; i < m_density; i++) {
		for (int j = 0; j < 2 * (m_density + 1); j++) {
			int idx = (i + j % 2) * (m_density + 1) + (j >> 1);
			m_geometry.indices.push_back(idx);
		}
	}*/
	for (int i = 0; i < m_density; i++) {
		for (int j = 0; j < m_density; j++) {
			m_geometry.indices.push_back((m_density + 1) * (i + 1) + (j + 1));
			m_geometry.indices.push_back((m_density + 1) * (i + 1) + j);
			m_geometry.indices.push_back((m_density + 1) * i + j);
			m_geometry.indices.push_back((m_density + 1) * i + j);
			m_geometry.indices.push_back((m_density + 1) * i + (j + 1));
			m_geometry.indices.push_back((m_density + 1) * (i + 1) + (j + 1));
		}
	}

	m_material = ResourceManager::Get().GetMaterial(source["material"]);
}

Water::~Water() {
	ObjectInstance::~ObjectInstance();
}

void Water::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	m_time += deltaTime;

	ShaderProgram* shaderProgram = SH(m_shaderType);
	shaderProgram->UseShader();
	shaderProgram->SetUniform("waveSpeed", m_waveSpeed);
	shaderProgram->SetUniform("time", m_time);

	ObjectInstance::Update(deltaTime, parentModelMatrix);
}

void Water::Draw() {
	ShaderProgram* shaderProgram = SH(m_shaderType);

	shaderProgram->UseShader();
	shaderProgram->SetUniform("mMatrix", m_globalModelMatrix);

	glm::vec3 colAlbedo = m_material->Albedo();
	shaderProgram->SetUniform("colAlbedo", colAlbedo);
	GLuint normalMap1 = m_material->NormalMap1();
	GLuint normalMap2 = m_material->NormalMap2();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, normalMap1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalMap2);
	CHECK_GL_ERROR();

	glm::vec3 emission = m_material->Emission();
	shaderProgram->SetUniform("colEmission", emission);

	float specular = m_material->Specular();
	shaderProgram->SetUniform("specular", specular);

	float roughness = m_material->Roughness();
	shaderProgram->SetUniform("roughness", roughness);

	float transmission = m_material->Transmission();
	shaderProgram->SetUniform("transmission", transmission);

	glBindVertexArray(m_geometry.vertexArrayObject);
	CHECK_GL_ERROR();
	glDrawElements(GL_TRIANGLES, m_geometry.numTriangles * 3, GL_UNSIGNED_INT, (void *) 0);
	CHECK_GL_ERROR();

	ObjectInstance::Draw();
}

bool Water::GenObjects() {
	ShaderProgram* shaderProgram = SH(m_shaderType);

	// Generating VBOs
	glGenBuffers(1, &(m_geometry.vertexBufferObject));
	glBindBuffer(GL_ARRAY_BUFFER, m_geometry.vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_geometry.verticesData.size(),
		m_geometry.verticesData.data(), GL_STATIC_DRAW);
	CHECK_GL_ERROR();

	// Generating EBO
	glGenBuffers(1, &(m_geometry.elementBufferObject));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_geometry.elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_geometry.numTriangles * 3,
		m_geometry.indices.data(), GL_STATIC_DRAW);
	CHECK_GL_ERROR();

	// Generating VAO
	glGenVertexArrays(1, &(m_geometry.vertexArrayObject));
	CHECK_GL_ERROR();

	// Connecting vertex attributes
	glBindVertexArray(m_geometry.vertexArrayObject);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ARRAY_BUFFER, m_geometry.vertexBufferObject);
	shaderProgram->EnableAttrib("position");
	shaderProgram->AttribFloat("position", 3, m_geometry.numAttributesPerVertex, 0);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_geometry.elementBufferObject);
	CHECK_GL_ERROR();

	glBindVertexArray(0);

	InitTextures(shaderProgram);

	return ObjectInstance::GenObjects();
}

void Water::InitTextures(ShaderProgram* shaderProgram) {
	shaderProgram->SetUniform("texNormal1", 0);
	shaderProgram->SetUniform("texNormal2", 1);
}
