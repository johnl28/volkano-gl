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
		
		void Move(glm::vec3 velocity);
		void Rotate(glm::vec3 deg);
		void Scale(glm::vec3 scale);

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetRotation() { return m_Rotation; }
		const glm::vec3& GetScale() { return m_Scale; }

	private:
		void AddAiMesh(aiMesh *aiMesh);

		void UpdateMeshPosition();
		void UpdateMeshRotation();
		void UpdateMeshScale();


	private:
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(1.0f);

		std::vector<std::unique_ptr<Mesh>> m_Meshes;
	};
}