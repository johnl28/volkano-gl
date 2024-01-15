#pragma once

#include "Core/CubeMap.h"
#include "Core/ShaderProgram.h"
#include "Model.h"

namespace glcore {

	class Skybox
	{
	public:
		Skybox(Model* model, CubeMap* cubemap, ShaderProgram* shader);

		Model* GetModel() { return m_Model; }
		CubeMap* GetCubemap() { return m_Cubemap; }
		ShaderProgram* GetShader() { return m_Shader; }


	private:
		Model* m_Model = nullptr;
		CubeMap* m_Cubemap = nullptr;
		ShaderProgram* m_Shader = nullptr;
	};

}
