
#include "Log.h"
#include "Model.h"


namespace glcore {

	void Model::Render(ShaderProgram* shader)
	{
		shader->Bind();
		for (auto& mesh : m_Meshes)
		{
			mesh->Bind();
			shader->SetUniformMatrix4fv("u_Transform", mesh->GetTransformMatrix());

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

	bool Model::Load(const std::string& filePath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate |
			aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
			!scene->mRootNode)
		{
			GLCORE_ERR("[Model] [ASSIMP] Failed to load model %s. Error: %s", filePath.c_str(), importer.GetErrorString());
			return false;
		}

		GLCORE_INFO("[Model]: Successfull loaded %s model, total meshes %d", filePath.c_str(), scene->mNumMeshes);

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			AddAiMesh(scene->mMeshes[i]);
		}


		return true;
	}

	void Model::Rotate(glm::vec3 deg)
	{
		for (auto& mesh : m_Meshes)
		{
			mesh->Rotate(deg);
		}
	}

	void Model::AddAiMesh(aiMesh* aiMesh)
	{

		std::vector<Vertex> vertices;


		for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
		{
			Vertex vertex;

			// Position
			vertex.position = glm::vec3(aiMesh->mVertices[i].x, aiMesh->mVertices[i].y, aiMesh->mVertices[i].z);

			// Texture Coordinates
			if (aiMesh->mTextureCoords[0]) {
				vertex.textureCoord = glm::vec2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
			}
			else {
				vertex.textureCoord = glm::vec2(0.0f, 0.0f);
			}

			// Normals
			vertex.normals = glm::vec3(0.0f);

			vertices.push_back(vertex);
		}

		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
		{
			aiFace face = aiMesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		auto myMesh = new Mesh(vertices.data(), sizeof(Vertex) * vertices.size(), indices.data(), indices.size());
		myMesh->Scale(glm::vec3(0.1));
		myMesh->Rotate(glm::vec3(-90.0f, 0.0f, 0.0f));
		m_Meshes.push_back(std::unique_ptr<Mesh>(myMesh));
	}

}
