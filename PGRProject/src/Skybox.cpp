//----------------------------------------------------------------------------------------
/**
 * \file       Skybox.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "Skybox.h"

void Skybox::GenSkybox() {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_SKYBOX);
	
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
	shaderProgram->EnableAttrib("position");
	shaderProgram->AttribFloat("position", 3, ATTRIBS_PER_VERTEX, 0);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_geometry.elementBufferObject);
	CHECK_GL_ERROR();

	glBindVertexArray(0);
}

void Skybox::Draw() {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_SKYBOX);
	
	shaderProgram->UseShader();
	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(100.0f));
	CHECK_GL_ERROR();

	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CW);
	glBindVertexArray(m_geometry.vertexArrayObject);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTex);
	CHECK_GL_ERROR();

	glDrawElements(GL_TRIANGLES, sizeof(skyboxIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
	CHECK_GL_ERROR();

	glDepthFunc(GL_LESS);
	glFrontFace(GL_CCW);
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
