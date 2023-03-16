#include "Object.h"
#include <iostream>

void ObjectInstance::Update(float deltaTime, const glm::mat4* parentModelMatrix) {
	m_LocalModelMatrix = ComputeModelMatrix();

	// if we have parent, multiply parent's matrix with ours
	if (parentModelMatrix != nullptr)
		m_Global_model_matrix = *parentModelMatrix * m_LocalModelMatrix;
	else
		m_Global_model_matrix = m_LocalModelMatrix;
	
	for (auto child : children) {
		if (child != nullptr)
			child->Update(deltaTime, &m_Global_model_matrix);
	}
}

void ObjectInstance::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, ShaderProgram *shaderProgram) {
	if (!m_EmptyObject) {
		shaderProgram->UseShader();
		glUniformMatrix4fv(shaderProgram->locations.pvmMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * m_Global_model_matrix));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Textures.diffuse);

		glBindVertexArray(m_Geometry.vertexArrayObject);
		glDrawElements(GL_TRIANGLES, m_Geometry.numTriangles * 3, GL_UNSIGNED_INT, nullptr);
		CHECK_GL_ERROR();
	}

	// process all children
	for (auto child : children) {
		if (child != nullptr)
			child->Draw(viewMatrix, projectionMatrix, shaderProgram);
	}
}

void ObjectInstance::UseLegacyMesh(const pgr::MeshData& meshData)
{
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

bool ObjectInstance::GenObjects(ShaderProgram *shaderProgram)
{
	if (!m_EmptyObject) {
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
	}

	for (auto child : children) {
		if (child != nullptr)
			child->GenObjects(shaderProgram);
	}
	return true;
}

void ObjectInstance::LoadAssimp(const std::string& filepath, bool joinMeshes) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, ASSIMP_LOAD_FLAGS);

	std::string assetsDirectory;
	const size_t lastSlashIdx = filepath.rfind('/');
	if (std::string::npos != lastSlashIdx) {
		assetsDirectory = filepath.substr(0, lastSlashIdx) + "/";
	}

	if (!scene) {
		std::cerr << "Failed to load aiScene" << std::endl;
		return;
	}

	if (joinMeshes) {
		// TODO
	}
	else if (scene->mNumMeshes == 1) {
		// TODO
	}
	else {
		m_EmptyObject = true;

		std::vector<Material*> materials;
		for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
			aiMaterial* importedMaterial = scene->mMaterials[i];
			Material* currentMaterial = new Material(importedMaterial, assetsDirectory);
			materials.push_back(currentMaterial);
		}


		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			children.push_back(new ObjectInstance(scene->mMeshes[i], materials[scene->mMeshes[i]->mMaterialIndex]));
		}
	}
}

void ObjectInstance::LoadCustom(const std::string& filepath, bool joinMeshes) {
	// TODO
}

glm::mat4 ObjectInstance::ComputeModelMatrix()
{
	glm::mat4 modelMat = glm::scale(glm::mat4(), m_Scale);
	modelMat = glm::toMat4(m_Rotation) * modelMat;
	modelMat = glm::translate(modelMat, m_Position);
	return modelMat;
}

ObjectInstance::ObjectInstance() {
}

ObjectInstance::ObjectInstance(const pgr::MeshData& meshData) {
	m_Shader_type = SHADER_TYPE_DEFAULT;
	UseLegacyMesh(meshData);
}

ObjectInstance::ObjectInstance(WavefrontObject* sourceWavefront) {
	m_Shader_type = SHADER_TYPE_DEFAULT;
}

ObjectInstance::ObjectInstance(const std::vector<WavefrontObject*>& sourceWavefront) {
	m_Shader_type = SHADER_TYPE_DEFAULT;
}

ObjectInstance::ObjectInstance(const std::string& name, bool useAssimp, bool joinMeshes) {
	m_Shader_type = SHADER_TYPE_DEFAULT;
	std::string sourceFilepath = OBJECT_PATH_PREFIX + name + "/" + name + ".obj";
	if (useAssimp) {
		LoadAssimp(sourceFilepath, joinMeshes);
	}
	else {
		LoadCustom(sourceFilepath, joinMeshes);
	}
	m_Scale = glm::vec3(DEFAULT_WAVEFRONT_SCALE);
}

ObjectInstance::ObjectInstance(aiMesh* mesh, Material *material) {
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

	m_Textures.diffuse = material->DiffuseMap();
}

ObjectInstance::~ObjectInstance() {
}
