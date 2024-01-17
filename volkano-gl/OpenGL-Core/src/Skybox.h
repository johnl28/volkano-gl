#pragma once

#include "Core/CubeMap.h"
#include "Core/ShaderProgram.h"
#include "Model.h"

namespace glcore {

	class Skybox
	{
	public:
		Skybox(Model* model, CubeMap* cubemap, ShaderProgram* shader);

		void SetEnabled(bool enabled) { m_Enabled = enabled; }
		bool IsEnabled() const { return m_Enabled; }

		const glm::vec4& GetAmbientColor() const { return m_AmbientColor; }
		void SetAmbientColor(const glm::vec4& color) { m_AmbientColor = color; }

		Model* GetModel() { return m_Model; }
		CubeMap* GetCubemap() { return m_Cubemap; }
		ShaderProgram* GetShader() { return m_Shader; }


	private:
		bool m_Enabled = true;
		glm::vec4 m_AmbientColor = glm::vec4(1);

		Model* m_Model = nullptr;
		CubeMap* m_Cubemap = nullptr;
		ShaderProgram* m_Shader = nullptr;
	};

}
