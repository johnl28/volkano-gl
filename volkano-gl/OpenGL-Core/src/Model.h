#pragma once
#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Core/ShaderProgram.h"
#include "Mesh.h"


namespace glcore {
	class Model
	{
	public:
		void Render(ShaderProgram *shader);
		bool Load(const std::string& filePath);
		
		bool IsLoaded() const { return m_Loaded; }

		const std::vector<std::unique_ptr<Mesh>> &GetMeshes() const { return m_Meshes; }

		// Transform
		void Move(const glm::vec3& velocity);
		void SetPosition(const glm::vec3& position);

		void Rotate(const glm::vec3& deg);
		void SetRotation(const glm::vec3& rotation);

		void Scale(const glm::vec3& scale);

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetRotation() { return m_Rotation; }
		const glm::vec3& GetScale() { return m_Scale; }

	private:
		void LoadAiMeshData(const aiMesh *aiMesh, const aiMaterial *aiMaterial);

		void UpdateMeshPosition();
		void UpdateMeshRotation();
		void UpdateMeshScale();


	private:
		bool m_Loaded = false;

		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);

		std::vector<std::unique_ptr<Mesh>> m_Meshes;
	};
}