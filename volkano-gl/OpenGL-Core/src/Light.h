#pragma once
#include "glm/glm.hpp"

#include "Core/ShaderProgram.h"
#include "Model.h"

namespace glcore {

	// This is just a prototype Light class that renders chosen 3D model where the light is placed
	// With the current approach the model used to represent a light cannot be reused
	// A good approach would be to use batch rendering and a Mesh/Model instantiation system

	class Light
	{
	public:
		Light(const glm::vec3& position, const glm::vec3& color);

		const Model* GetModel() const { return m_Model; }
		void SetModel(Model* model);

		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetColor(const glm::vec3& color) { m_Color = color; }
		const glm::vec3& GetColor() const { return m_Color; }

	private:
		void UpdateModel();

	private:
		Model* m_Model = nullptr;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
	};

}
