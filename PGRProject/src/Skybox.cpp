#include "Skybox.h"

void Skybox::GenSkybox(ShaderProgram* shaderProgram) {
	LoadCubemap();
	
	// Generating VBO
	glGenBuffers(1, &(m_geometry.vertexBufferObject));
	glBindBuffer(GL_ARRAY_BUFFER, m_geometry.vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	CHECK_GL_ERROR();

	// Generating EBO
	glGenBuffers(1, &(m_geometry.elementBufferObject));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_geometry.elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);
	CHECK_GL_ERROR();

	// Generating VAO
	glGenVertexArrays(1, &(m_geometry.vertexArrayObject));
	CHECK_GL_ERROR();

	// Connecting vertex attributes
	glBindVertexArray(m_geometry.vertexArrayObject);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ARRAY_BUFFER, m_geometry.vertexBufferObject);
	//glEnableVertexAttribArray(shaderProgram->locations.position);
	shaderProgram->EnableAttrib("position");
	//glVertexAttribPointer(shaderProgram->locations.position, 3, GL_FLOAT, GL_FALSE, ATTRIBS_PER_VERTEX * sizeof(float), (void*)0);
	shaderProgram->AttribFloat("position", 3, ATTRIBS_PER_VERTEX, 0);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_geometry.elementBufferObject);
	CHECK_GL_ERROR();

	glBindVertexArray(0);
}

void Skybox::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram* shaderProgram) {
	shaderProgram->UseShader();
	//glUniformMatrix4fv(shaderProgram->locations.pvmMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix));
	glm::mat4 pv = projectionMatrix * viewMatrix;
	shaderProgram->SetUniform("pvMatrix", pv);
	CHECK_GL_ERROR();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTex);
	CHECK_GL_ERROR();

	glBindVertexArray(m_geometry.vertexArrayObject);
	glDrawElements(GL_TRIANGLES, sizeof(skyboxIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
	CHECK_GL_ERROR();
}

void Skybox::LoadCubemap() {
	glGenTextures(1, &m_cubemapTex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	pgr::loadTexImage2D(SKYBOX_DIR_PREFIX + std::string("px.png"), GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	pgr::loadTexImage2D(SKYBOX_DIR_PREFIX + std::string("nx.png"), GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	pgr::loadTexImage2D(SKYBOX_DIR_PREFIX + std::string("py.png"), GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	pgr::loadTexImage2D(SKYBOX_DIR_PREFIX + std::string("ny.png"), GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	pgr::loadTexImage2D(SKYBOX_DIR_PREFIX + std::string("pz.png"), GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	pgr::loadTexImage2D(SKYBOX_DIR_PREFIX + std::string("nz.png"), GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
}
