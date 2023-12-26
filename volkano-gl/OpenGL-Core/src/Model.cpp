
#include "Log.h"
#include "Model.h"


namespace glcore {

	void Model::Render(ShaderProgram* shader)
	{
		// Bind shader
		shader->Bind();

		// Render each mesh in the model
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

		const auto aiScene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
		{
			GLCORE_ERR("[Model] [ASSIMP] Failed to load model %s. Error: %s", filePath.c_str(), importer.GetErrorString());
			return false;
		}

		GLCORE_INFO("[Model] Successfull loaded %s. Meshes: %d, Textures: %d, Materials: %d", 
			filePath.c_str(), aiScene->mNumMeshes, aiScene->mNumTextures, aiScene->mNumMaterials);


		for (unsigned int i = 0; i < aiScene->mNumMeshes; i++)
		{
			AddAiMesh(aiScene->mMeshes[i]);
		}


		return true;
	}


	void Model::AddAiMesh(aiMesh* aiMesh)
	{
		if (!aiMesh)
		{
			GLCORE_ERR("[Model] Cannot add ASSIMP mesh, null pointer provided.");
			return;
		}

		std::vector<Vertex> vertices;


		for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
		{
			Vertex vertex;

			// Position
			vertex.position = glm::vec3(aiMesh->mVertices[i].x, aiMesh->mVertices[i].y, aiMesh->mVertices[i].z);

			// Texture Coordinates
			if (aiMesh->HasTextureCoords(0))
			{
				vertex.textureCoord = glm::vec2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
			}
			else
			{
				vertex.textureCoord = glm::vec2(0.0f, 0.0f);
			}

			// Set Normals
			if (aiMesh->HasNormals())
			{
				vertex.normals = glm::vec3(aiMesh->mNormals[i].x, aiMesh->mNormals[i].y, aiMesh->mNormals[i].z);
			}

			vertices.push_back(vertex);
		}

		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
		{
			const aiFace& face = aiMesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		auto myMesh = new Mesh(vertices.data(), sizeof(Vertex) * vertices.size(), indices.data(), indices.size());
		m_Meshes.push_back(std::unique_ptr<Mesh>(myMesh));

		GLCORE_INFO("[Model] [Mesh] Successfull loaded. Faces: %d, Vertices: %d, Has Normals: %d", aiMesh->mNumFaces, aiMesh->mNumVertices, aiMesh->HasNormals());
	}



	void Model::Move(glm::vec3 velocity)
	{
		m_Position += velocity;
		UpdateMeshPosition();
	}

	void Model::UpdateMeshPosition()
	{
		for (auto& mesh : m_Meshes)
		{
			mesh->SetPosition(m_Position);
		}
	}

	void Model::Rotate(glm::vec3 deg)
	{
		m_Rotation += deg;
		UpdateMeshRotation();
	}

	void Model::UpdateMeshRotation()
	{
		for (auto& mesh : m_Meshes)
		{
			mesh->SetRotation(m_Rotation);
		}
	}

	void Model::Scale(glm::vec3 scale)
	{
		m_Scale = scale;
		UpdateMeshScale();
	}

	void Model::UpdateMeshScale()
	{
		for (auto& mesh : m_Meshes)
		{
			mesh->SetScale(m_Scale);
		}
	}

}
