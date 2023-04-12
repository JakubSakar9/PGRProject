#include "StaticObject.h"

StaticObject::StaticObject(const pgr::MeshData& meshData) {
	UseLegacyMesh(meshData);
}

StaticObject::StaticObject(aiMesh* mesh, Material* material) {
	m_scale = glm::vec3(1.0f);

	m_geometry.numVertices = mesh->mNumVertices;
	m_geometry.numTriangles = mesh->mNumFaces;
	m_geometry.numAttributes = mesh->mNumVertices * VERTEX_SIZE;
	m_geometry.numAttributesPerVertex = VERTEX_SIZE;
	m_geometry.verticesData.resize(m_geometry.numAttributes);
	m_geometry.indices.resize(3 * m_geometry.numTriangles);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		const aiVector3D& position = mesh->mVertices[i];
		const aiVector3D& normals = mesh->mNormals[i];
		const aiVector3D& texCoords = mesh->mTextureCoords[0][i];

		m_geometry.verticesData[VERTEX_SIZE * i + 0] = position.x;
		m_geometry.verticesData[VERTEX_SIZE * i + 1] = position.y;
		m_geometry.verticesData[VERTEX_SIZE * i + 2] = position.z;
		m_geometry.verticesData[VERTEX_SIZE * i + 3] = normals.x;
		m_geometry.verticesData[VERTEX_SIZE * i + 4] = normals.y;
		m_geometry.verticesData[VERTEX_SIZE * i + 5] = normals.z;
		m_geometry.verticesData[VERTEX_SIZE * i + 6] = texCoords.x;
		m_geometry.verticesData[VERTEX_SIZE * i + 7] = 1 - texCoords.y;
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& face = mesh->mFaces[i];

		m_geometry.indices[3 * i + 0] = face.mIndices[0];
		m_geometry.indices[3 * i + 1] = face.mIndices[1];
		m_geometry.indices[3 * i + 2] = face.mIndices[2];
	}

	m_material = material;
}

StaticObject::StaticObject(nlohmann::json source) {
	InitTransform(source);
	InitChildren(source);

	aiMesh* mesh = ResourceManager::Get().GetMesh(
		source["source"], source["objname"], source["sourceType"]);

}

StaticObject::~StaticObject() {
	ObjectInstance::~ObjectInstance();
}


void StaticObject::UseLegacyMesh(const pgr::MeshData& meshData) {
	m_geometry.numAttributesPerVertex = meshData.nAttribsPerVertex;
	m_geometry.numAttributes = meshData.nAttribsPerVertex * meshData.nVertices;
	m_geometry.numTriangles = meshData.nTriangles;
	m_geometry.verticesData.resize(m_geometry.numAttributes);
	m_geometry.indices.resize(3 * m_geometry.numTriangles);

	std::copy(meshData.verticesInterleaved,
		meshData.verticesInterleaved + m_geometry.numAttributes,
		m_geometry.verticesData.begin());
	std::copy(meshData.triangles,
		meshData.triangles + 3 * m_geometry.numTriangles,
		m_geometry.indices.begin());
}

void StaticObject::Update(float deltaTime,
	const glm::mat4* parentModelMatrix, glm::vec3 cameraPos) {
	m_cameraPosition = cameraPos;
	ObjectInstance::Update(deltaTime, parentModelMatrix, cameraPos);
}

void StaticObject::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	ShaderProgram* shaderProgram = SH(m_shaderType);

	shaderProgram->UseShader();
	glm::mat4x4 pv = projectionMatrix * viewMatrix;
	shaderProgram->SetUniform("pvMatrix", pv);
	shaderProgram->SetUniform("mMatrix", m_globalModelMatrix);
	shaderProgram->SetUniform("cameraPosition", m_cameraPosition);

	shaderProgram->SetUniform("useTexDiffuse", (int) m_material->DiffuseMap());
	glm::vec3 colDiffuse = m_material->Diffuse();
	shaderProgram->SetUniform("colDiffuse", colDiffuse);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_material->DiffuseMap());
	CHECK_GL_ERROR();

	glm::vec3 colSpecular = m_material->Specular();
	float specularExp = m_material->SpecularExponent();
	shaderProgram->SetUniform("colSpecular", colSpecular);
	shaderProgram->SetUniform("specularExponent", specularExp);
	
	float dissolveFactor = m_material->DissolveFactor();
	shaderProgram->SetUniform("dissolveFactor", dissolveFactor);

	glBindVertexArray(m_geometry.vertexArrayObject);
	CHECK_GL_ERROR();
	glDrawElements(GL_TRIANGLES, m_geometry.numTriangles * 3, GL_UNSIGNED_INT, nullptr);
	CHECK_GL_ERROR();

	ObjectInstance::Draw(viewMatrix, projectionMatrix);
}

bool StaticObject::GenObjects(ShaderType shaderType) {
	m_shaderType = shaderType;
	ShaderProgram* shaderProgram = SH(shaderType);

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

	return ObjectInstance::GenObjects(shaderType);
}
