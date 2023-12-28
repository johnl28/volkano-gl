#pragma once
#include "glm/glm.hpp"

#include "Core/ShaderProgram.h"
#include "Model.h"

namespace glcore {

	class Light
	{
	public:
		Light();
		void Render(ShaderProgram *shader);

		const glm::vec3& GetColor() const { return m_Color; }

	private:
		std::unique_ptr<Model> m_Model = nullptr;
		glm::vec3 m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
	};

}
