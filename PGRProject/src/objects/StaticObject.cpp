//----------------------------------------------------------------------------------------
/**
 * \file       StaticObject.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "StaticObject.h"

StaticObject::StaticObject(nlohmann::json source) {
	InitTransform(source);

	MeshData* mesh = ResourceManager::Get().GetMesh(
		source["source"], source["objName"], source["sourceType"]);

	m_geometry.numVertices = mesh->numVertices;
	m_geometry.numTriangles = mesh->numFaces;
	m_geometry.numAttributes = mesh->numVertices * VERTEX_SIZE;
	m_geometry.numAttributesPerVertex = VERTEX_SIZE;
	m_geometry.verticesData.resize(m_geometry.numAttributes);
	m_geometry.indices.resize(3 * m_geometry.numTriangles);

	for (unsigned int i = 0; i < mesh->numVertices; i++) {
		const glm::vec3& position = mesh->vertices[i];
		const glm::vec3& normals = mesh->normals[i];
		const glm::vec2& texCoords = mesh->texCoords[i];

		m_geometry.verticesData[VERTEX_SIZE * i + 0] = position.x;
		m_geometry.verticesData[VERTEX_SIZE * i + 1] = position.y;
		m_geometry.verticesData[VERTEX_SIZE * i + 2] = position.z;
		m_geometry.verticesData[VERTEX_SIZE * i + 3] = normals.x;
		m_geometry.verticesData[VERTEX_SIZE * i + 4] = normals.y;
		m_geometry.verticesData[VERTEX_SIZE * i + 5] = normals.z;
		m_geometry.verticesData[VERTEX_SIZE * i + 6] = texCoords.x;
		m_geometry.verticesData[VERTEX_SIZE * i + 7] = texCoords.y;
	}

	for (unsigned int i = 0; i < mesh->numFaces; i++) {
		const glm::ivec3& face = mesh->faces[i];
		m_geometry.indices[3 * i + 0] = face.x;
		m_geometry.indices[3 * i + 1] = face.y;
		m_geometry.indices[3 * i + 2] = face.z;
	}

	m_material = ResourceManager::Get().GetMaterial(source["material"]);
}

void StaticObject::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
}

void StaticObject::Draw() {
	ShaderProgram* shaderProgram = SH(m_shaderType);

	shaderProgram->UseShader();
	shaderProgram->SetUniform("mMatrix", m_globalModelMatrix);

	glm::mat4 normalMat = glm::toMat4(m_globalRotation);
	shaderProgram->SetUniform("normalMatrix", normalMat);

	glm::vec3 colAlbedo = m_material->Albedo();
	shaderProgram->SetUniform("colAlbedo", colAlbedo);
	GLint albedoMap = m_material->AlbedoMap();
	if (albedoMap) {
		shaderProgram->SetUniform("useTexAlbedo", 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_material->AlbedoMap());
	}
	else {
		shaderProgram->SetUniform("useTexAlbedo", 0);
	}
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
	glDrawElements(GL_TRIANGLES, m_geometry.numTriangles * 3, GL_UNSIGNED_INT, nullptr);
	CHECK_GL_ERROR();

	ObjectInstance::Draw();
}

bool StaticObject::GenObjects(std::vector<ObjectInstance*>& transparentObjects) {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_DEFAULT);

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
	shaderProgram->EnableAttrib("normal");
	shaderProgram->AttribFloat("normal", 3, m_geometry.numAttributesPerVertex, 3);
	shaderProgram->EnableAttrib("texCoords");
	shaderProgram->AttribFloat("texCoords", 2, m_geometry.numAttributesPerVertex, 6);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_geometry.elementBufferObject);
	CHECK_GL_ERROR();

	glBindVertexArray(0);

	InitTextures(shaderProgram);

	return ObjectInstance::GenObjects(transparentObjects);
}

void StaticObject::InitTextures(ShaderProgram *shaderProgram) {
	shaderProgram->UseShader();
	shaderProgram->SetUniform("texAlbedo", 0);
}

void StaticObject::ShowProperties() {
	ObjectInstance::ShowProperties();

	m_material->ShowProperties();
}
