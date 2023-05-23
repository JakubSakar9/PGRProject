//----------------------------------------------------------------------------------------
/**
 * \file       EyeObject.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "EyeObject.h"

EyeObject::EyeObject(nlohmann::json source) {
	InitTransform(source);

	MeshData* mesh = ResourceManager::Get().GetMesh(
		source["source"], source["objName"], source["sourceType"]);

	m_geometry.numVertices = mesh->numVertices;
	m_geometry.numTriangles = mesh->numFaces;
	m_geometry.verticesData.resize(5 * m_geometry.numVertices);
	m_geometry.indices.resize(3 * m_geometry.numTriangles);

	for (unsigned int i = 0; i < mesh->numVertices; i++) {
		const glm::vec3& position = mesh->vertices[i];
		const glm::vec2& texCoords = mesh->texCoords[i];

		m_geometry.verticesData[5 * i + 0] = position.x;
		m_geometry.verticesData[5 * i + 1] = position.y;
		m_geometry.verticesData[5 * i + 2] = position.z;
		m_geometry.verticesData[5 * i + 3] = texCoords.x;
		m_geometry.verticesData[5 * i + 4] = texCoords.y;
	}

	for (unsigned int i = 0; i < mesh->numFaces; i++) {
		const glm::ivec3& face = mesh->faces[i];
		m_geometry.indices[3 * i + 0] = face.x;
		m_geometry.indices[3 * i + 1] = face.y;
		m_geometry.indices[3 * i + 2] = face.z;
	}

	m_material = ResourceManager::Get().GetMaterial(source["material"]);
}

void EyeObject::Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) {
	m_animTime += deltaTime / 1000.0f;
	if (m_animTime > 1.0f) {
		m_animTime -= 1.0f;
	}

	int animKeyframe = 0;
	float keyFrameTime = 0.0f;
	for (int i = 0; i < NUM_KEYFRAMES; i++) {
		keyFrameTime += animTimes[i];
		if (keyFrameTime > m_animTime) {
			break;
		}
		animKeyframe++;
	}
	m_frameId = animFrames[animKeyframe];

	ObjectInstance::Update(deltaTime, parentModelMatrix, parentRotation);
}

void EyeObject::Draw() {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_EYE);

	shaderProgram->UseShader();
	shaderProgram->SetUniform("mMatrix", m_globalModelMatrix);
	shaderProgram->SetUniform("frameId", m_frameId);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_material->AlbedoMap());
	CHECK_GL_ERROR();

	glBindVertexArray(m_geometry.vertexArrayObject);
	CHECK_GL_ERROR();
	glDrawElements(GL_TRIANGLES, m_geometry.numTriangles * 3, GL_UNSIGNED_INT, nullptr);
	CHECK_GL_ERROR();

	ObjectInstance::Draw();
}

bool EyeObject::GenObjects(std::vector<ObjectInstance*>& transparentObjects) {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_EYE);

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

	shaderProgram->UseShader();
	shaderProgram->SetUniform("numFrames", NUM_FRAMES);

	glBindBuffer(GL_ARRAY_BUFFER, m_geometry.vertexBufferObject);
	shaderProgram->EnableAttrib("position");
	shaderProgram->AttribFloat("position", 3, 5, 0);
	shaderProgram->EnableAttrib("texCoords");
	shaderProgram->AttribFloat("texCoords", 2, 5, 3);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_geometry.elementBufferObject);
	CHECK_GL_ERROR();

	glBindVertexArray(0);

	InitTextures(shaderProgram);

	return ObjectInstance::GenObjects(transparentObjects);
}

void EyeObject::InitTextures(ShaderProgram* shaderProgram) {
	glActiveTexture(GL_TEXTURE0);
	shaderProgram->SetUniform("texAlbedo", 0);
}

void EyeObject::ShowProperties() {
	ObjectInstance::ShowProperties();
}
