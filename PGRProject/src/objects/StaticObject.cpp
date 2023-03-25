#include "StaticObject.h"

StaticObject::StaticObject(const pgr::MeshData& meshData) {
	m_Shader_type = SHADER_TYPE_DEFAULT;
	UseLegacyMesh(meshData);
}

StaticObject::StaticObject(WavefrontObject* sourceWavefront) {
	// Not yet implemented
}

StaticObject::StaticObject(const std::vector<WavefrontObject*>& sourceWavefront) {
	// Not yet implemented
}

StaticObject::StaticObject(const std::string& name, bool useAssimp) {
	m_Shader_type = SHADER_TYPE_DEFAULT;
	std::string sourceFilepath = OBJECT_PATH_PREFIX + name + "/" + name + ".obj";
	if (useAssimp) {
		LoadAssimp(sourceFilepath);
	}
	else {
		LoadCustom(sourceFilepath);
	}
	m_Scale = glm::vec3(DEFAULT_WAVEFRONT_SCALE);
}

StaticObject::StaticObject(aiMesh* mesh, Material* material)
{
	m_Shader_type = SHADER_TYPE_DEFAULT;
	m_Scale = glm::vec3(1.0f);

	m_Geometry.numVertices = mesh->mNumVertices;
	m_Geometry.numTriangles = mesh->mNumFaces;
	m_Geometry.numAttributes = mesh->mNumVertices * VERTEX_SIZE;
	m_Geometry.numAttributesPerVertex = VERTEX_SIZE;
	m_Geometry.verticesData.resize(m_Geometry.numAttributes);
	m_Geometry.indices.resize(3 * m_Geometry.numTriangles);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		const aiVector3D& position = mesh->mVertices[i];
		const aiVector3D& texCoords = mesh->mTextureCoords[0][i];

		m_Geometry.verticesData[VERTEX_SIZE * i + 0] = position.x;
		m_Geometry.verticesData[VERTEX_SIZE * i + 1] = position.y;
		m_Geometry.verticesData[VERTEX_SIZE * i + 2] = position.z;
		m_Geometry.verticesData[VERTEX_SIZE * i + 3] = texCoords.x;
		m_Geometry.verticesData[VERTEX_SIZE * i + 4] = 1 - texCoords.y;
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& face = mesh->mFaces[i];

		m_Geometry.indices[3 * i + 0] = face.mIndices[0];
		m_Geometry.indices[3 * i + 1] = face.mIndices[1];
		m_Geometry.indices[3 * i + 2] = face.mIndices[2];
	}

	m_Material = material;
}

StaticObject::~StaticObject() {
	ObjectInstance::~ObjectInstance();
}


void StaticObject::UseLegacyMesh(const pgr::MeshData& meshData) {
	m_Geometry.numAttributesPerVertex = meshData.nAttribsPerVertex;
	m_Geometry.numAttributes = meshData.nAttribsPerVertex * meshData.nVertices;
	m_Geometry.numTriangles = meshData.nTriangles;
	m_Geometry.verticesData.resize(m_Geometry.numAttributes);
	m_Geometry.indices.resize(3 * m_Geometry.numTriangles);

	std::copy(meshData.verticesInterleaved,
		meshData.verticesInterleaved + m_Geometry.numAttributes,
		m_Geometry.verticesData.begin());
	std::copy(meshData.triangles,
		meshData.triangles + 3 * m_Geometry.numTriangles,
		m_Geometry.indices.begin());
}

void StaticObject::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	ObjectInstance::Update(deltaTime, parentModelMatrix);
}

void StaticObject::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram* shaderProgram) {
	shaderProgram->UseShader();
	glUniformMatrix4fv(shaderProgram->locations.pvmMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * m_Global_model_matrix));

	glUniform1i(shaderProgram->locations.useTexDiffuse, m_Material->DiffuseMap());
	CHECK_GL_ERROR();
	glm::vec3 colDiffuse = m_Material->Diffuse();
	glUniform3f(shaderProgram->locations.colDiffuse, colDiffuse.x, colDiffuse.y, colDiffuse.z);
	CHECK_GL_ERROR();
	glActiveTexture(GL_TEXTURE0);
	CHECK_GL_ERROR();
	glBindTexture(GL_TEXTURE_2D, m_Material->DiffuseMap());
	CHECK_GL_ERROR();

	glBindVertexArray(m_Geometry.vertexArrayObject);
	CHECK_GL_ERROR();
	glDrawElements(GL_TRIANGLES, m_Geometry.numTriangles * 3, GL_UNSIGNED_INT, nullptr);
	CHECK_GL_ERROR();

	ObjectInstance::Draw(viewMatrix, projectionMatrix, shaderProgram);
}

bool StaticObject::GenObjects(ShaderProgram *shaderProgram) {
	// Generating VBOs
	glGenBuffers(1, &(m_Geometry.vertexBufferObject));
	glBindBuffer(GL_ARRAY_BUFFER, m_Geometry.vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Geometry.verticesData.size(), m_Geometry.verticesData.data(), GL_STATIC_DRAW);
	CHECK_GL_ERROR();

	// Generating EBO
	glGenBuffers(1, &(m_Geometry.elementBufferObject));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Geometry.elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Geometry.numTriangles * 3, m_Geometry.indices.data(), GL_STATIC_DRAW);
	CHECK_GL_ERROR();

	// Generating VAO
	glGenVertexArrays(1, &(m_Geometry.vertexArrayObject));
	CHECK_GL_ERROR();

	// Connecting vertex attributes
	glBindVertexArray(m_Geometry.vertexArrayObject);
	CHECK_GL_ERROR();

	glBindBuffer(GL_ARRAY_BUFFER, m_Geometry.vertexBufferObject);
	glEnableVertexAttribArray(shaderProgram->locations.position);
	glVertexAttribPointer(shaderProgram->locations.position, 3, GL_FLOAT, GL_FALSE, m_Geometry.numAttributesPerVertex * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(shaderProgram->locations.texCoords);
	glVertexAttribPointer(shaderProgram->locations.texCoords, 2, GL_FLOAT, GL_FALSE, m_Geometry.numAttributesPerVertex * sizeof(float), (void*) (3 * sizeof(float)));
	CHECK_GL_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Geometry.elementBufferObject);
	CHECK_GL_ERROR();

	glBindVertexArray(0);

	return ObjectInstance::GenObjects(shaderProgram);
}

void StaticObject::LoadAssimp(const std::string& filepath) {
	// Not yet implemented
}

void StaticObject::LoadCustom(const std::string& filepath) {
	// Not yet implemented
}
