#pragma once
#include <memory>

#include "glm/glm.hpp"

#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"
#include "Core/IndexBuffer.h"
#include "Core/Texture.h"

 
namespace glcore {

	class Mesh
	{
	public:
		Mesh(const void *vertexData, size_t vertexDataSize, const GLuint *indexData, GLuint indexCount);

		const glm::mat4& GetTransformMatrix();

		GLuint GetIndexCount() const { return m_indexBuffer->GetCount(); }

		void Bind() const;
		void UnBind() const;

	private:
		glm::mat4 m_transformMatrix = glm::mat4(1.0f);
		glm::vec3 m_position = glm::vec3(0.0f);
		glm::vec3 m_rotation = glm::vec3(0.0f);
		glm::vec3 m_scale = glm::vec3(1.0f);

	private:
		std::unique_ptr<VertexArray> m_vertexArray;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<Texture> m_texture;
	};

}
