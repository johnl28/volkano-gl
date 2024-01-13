
#include "Log.h"
#include "Model.h"


namespace glcore {

	void Model::Render(ShaderProgram* shader)
	{
		if (!m_Loaded)
		{
			GLCORE_ERR("[Model] Cannot render a model that is not loaded.");
			return;
		}


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

		// aiProcess_PreTransformVertices is provisionally
		// The mesh vertex position is pre-transformed based on the node's transformation matrix
		// That makes a mesh unusable individually

		const auto aiScene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_PreTransformVertices);

		if (!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
		{
			GLCORE_ERR("[Model] [ASSIMP] Failed to load model %s. Error: %s", filePath.c_str(), importer.GetErrorString());
			return false;
		}
		else if (!aiScene->HasMeshes())
		{
			GLCORE_ERR("[Model] Failed to load model %s. This model has no meshes.", filePath.c_str());
			return false;
		}


		GLCORE_INFO("[Model] Successfull loaded %s. Meshes: %d, Textures: %d, Materials: %d, Lights: %d, Cameras: %d", 
			filePath.c_str(), aiScene->mNumMeshes, aiScene->mNumTextures, aiScene->mNumMaterials, aiScene->mNumLights, aiScene->mNumCameras);

		LoadAiNode(aiScene, aiScene->mRootNode);

		m_Loaded = true;
		return true;
	}


	void Model::LoadAiNode(const aiScene* scene, const aiNode* node)
	{

		// Load Meshes within the node
		for (auto i = 0; i < node->mNumMeshes; ++i)
		{
			auto meshData = scene->mMeshes[node->mMeshes[i]];

			LoadAiMeshData(meshData, scene->mMaterials[meshData->mMaterialIndex]);
		}

		// Load the child nodes
		for (auto x = 0; x < node->mNumChildren; ++x)
		{
			LoadAiNode(scene, node->mChildren[x]);
		}

		GLCORE_INFO("[Model] [Node] Successfull loaded Node %s.", node->mName.C_Str());
	}

	void Model::LoadAiMeshData(const aiMesh* aiMesh, const aiMaterial* aiMaterial)
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
			else
			{
				vertex.normals = glm::vec3(0.0f);
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


		aiString path;
		//aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		aiMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, &path);
		GLCORE_INFO("TEST count %s", path.C_Str());

		std::string sPath;
		sPath.append("assets/");
		sPath.append(path.C_Str());

		auto myMesh = new Mesh(vertices.data(), sizeof(Vertex) * vertices.size(), indices.data(), indices.size());
		myMesh->LoadTexture(sPath);
		m_Meshes.push_back(std::unique_ptr<Mesh>(myMesh));

		GLCORE_INFO("[Model] [Mesh] Successfull loaded mesh %s. Faces: %d, Vertices: %d, Has Normals: %d", 
		 aiMesh->mName.C_Str(),	aiMesh->mNumFaces, aiMesh->mNumVertices, aiMesh->HasNormals());
	}



	void Model::Move(const glm::vec3& velocity)
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

	void Model::Rotate(const glm::vec3& deg)
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

	void Model::Scale(const glm::vec3& scale)
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
