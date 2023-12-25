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
		
		void Rotate(glm::vec3 deg);


	private:
		void AddAiMesh(aiMesh *aiMesh);
	private:

		std::vector<std::unique_ptr<Mesh>> m_Meshes;
	};
}