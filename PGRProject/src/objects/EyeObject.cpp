#include "EyeObject.h"

EyeObject::EyeObject(aiMesh* mesh, Material* material) {
	m_scale = glm::vec3(1.0f);

	m_geometry.numVertices = mesh->mNumVertices;
	m_geometry.numTriangles = mesh->mNumFaces;
	m_geometry.verticesData.resize(5 * m_geometry.numVertices);
	m_geometry.indices.resize(3 * m_geometry.numTriangles);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		const aiVector3D& position = mesh->mVertices[i];
		const aiVector3D& normals = mesh->mNormals[i];
		const aiVector3D& texCoords = mesh->mTextureCoords[0][i];

		m_geometry.verticesData[5 * i + 0] = position.x;
		m_geometry.verticesData[5 * i + 1] = position.y;
		m_geometry.verticesData[5 * i + 2] = position.z;
		m_geometry.verticesData[5 * i + 3] = texCoords.x;
		m_geometry.verticesData[5 * i + 4] = 1 - texCoords.y;
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& face = mesh->mFaces[i];

		m_geometry.indices[3 * i + 0] = face.mIndices[0];
		m_geometry.indices[3 * i + 1] = face.mIndices[1];
		m_geometry.indices[3 * i + 2] = face.mIndices[2];
	}

	m_material = material;
	m_animTime = 0.0f;
}

void EyeObject::Update(float deltaTime,
	const glm::mat4* parentModelMatrix, glm::vec3 cameraPos) {
	m_cameraPosition = cameraPos;

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

	ObjectInstance::Update(deltaTime, parentModelMatrix, cameraPos);
}

void EyeObject::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	ShaderProgram* shaderProgram = SH(SHADER_TYPE_EYE);

	shaderProgram->UseShader();
	glm::mat4x4 pv = projectionMatrix * viewMatrix;
	shaderProgram->SetUniform("pvMatrix", pv);
	shaderProgram->SetUniform("mMatrix", m_globalModelMatrix);
	shaderProgram->SetUniform("frameId", m_frameId);
	
	//glm::vec3 colDiffuse = m_material->Diffuse();
	//shaderProgram->SetUniform("colDiffuse", colDiffuse);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_material->DiffuseMap());
	CHECK_GL_ERROR();

	glBindVertexArray(m_geometry.vertexArrayObject);
	CHECK_GL_ERROR();
	glDrawElements(GL_TRIANGLES, m_geometry.numTriangles * 3, GL_UNSIGNED_INT, nullptr);
	CHECK_GL_ERROR();

	ObjectInstance::Draw(viewMatrix, projectionMatrix);
}

bool EyeObject::GenObjects(ShaderType shaderType) {
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

	return ObjectInstance::GenObjects(shaderType);
}
