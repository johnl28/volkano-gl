
#include "Log.h"
#include "Model.h"


namespace glcore {

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


		GLCORE_DEBUG("[Model] Successfull loaded %s. Meshes: %d, Textures: %d, Materials: %d, Lights: %d, Cameras: %d", 
			filePath.c_str(), aiScene->mNumMeshes, aiScene->mNumTextures, aiScene->mNumMaterials, aiScene->mNumLights, aiScene->mNumCameras);

		LoadAiNode(aiScene, aiScene->mRootNode);

		m_Loaded = true;
		return true;
	}

	Mesh* Model::GetMesh(int index) const
	{
		if (index >= m_Meshes.size())
		{
			return nullptr;
		}

		return m_Meshes[index].get();
	}


	void Model::LoadAiNode(const aiScene* scene, const aiNode* node)
	{

		// Load Meshes within the node
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			auto meshData = scene->mMeshes[node->mMeshes[i]];

			LoadAiMeshData(meshData, scene->mMaterials[meshData->mMaterialIndex]);
		}

		// Load the child nodes
		for (unsigned int x = 0; x < node->mNumChildren; ++x)
		{
			LoadAiNode(scene, node->mChildren[x]);
		}

		GLCORE_DEBUG("[Model] [Node] Successfull loaded Node %s.", node->mName.C_Str());
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


		auto myMesh = new Mesh(vertices.data(), sizeof(Vertex) * vertices.size(), indices.data(), indices.size());

		//GLCORE_WARN("[Model] [Material] Material name: %s, Diffuse Textures: %d, Ambient Textures: %d", 
		//	aiMaterial->GetName().C_Str(), aiMaterial->GetTextureCount(aiTextureType_DIFFUSE), aiMaterial->GetTextureCount(aiTextureType_NONE));


		aiString texturePath;
		aiMaterial->GetTextureCount(aiTextureType_DIFFUSE);
		aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
		if (texturePath.length)
		{
			std::string fullPath("assets/textures/");
			fullPath.append(texturePath.C_Str());

			myMesh->LoadTexture(fullPath);
		}
		aiColor3D color(0.f, 0.f, 0.f);
		aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);

		m_Meshes.push_back(std::unique_ptr<Mesh>(myMesh));

		GLCORE_DEBUG("[Model] [Mesh] Successfull loaded mesh %s. Faces: %d, Vertices: %d, Has Normals: %d",
		 aiMesh->mName.C_Str(),	aiMesh->mNumFaces, aiMesh->mNumVertices, aiMesh->HasNormals());
	}



	void Model::Move(const glm::vec3& velocity)
	{
		m_Position += velocity;
		UpdateMeshPosition();
	}

	void Model::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
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

	void Model::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
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
