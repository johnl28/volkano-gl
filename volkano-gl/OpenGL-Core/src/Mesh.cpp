#include "Mesh.h"

#include "glm/gtc/matrix_transform.hpp"

namespace glcore {

	Mesh::Mesh(const void* vertexData, size_t vertexDataSize, const GLuint* indexData, GLuint indexCount)
	{
		m_vertexArray = std::make_unique<VertexArray>();
		m_vertexBuffer = std::make_unique<VertexBuffer>(vertexData, vertexDataSize);
		m_indexBuffer = std::make_unique<IndexBuffer>(indexData, indexCount);

		m_vertexArray->AddAttribute<GLfloat>(3);
		m_vertexArray->AddAttribute<GLfloat>(2);
		m_vertexArray->AddAttribute<GLfloat>(3);
		m_vertexArray->CreateAttribPointers();

		m_vertexArray->UnBind();
		m_vertexBuffer->UnBind();
		m_indexBuffer->UnBind();
	}

	const glm::mat4& Mesh::GetTransformMatrix()
	{
		m_transformMatrix = glm::mat4(1.0f);
		m_transformMatrix = glm::translate(m_transformMatrix, m_position);
		m_transformMatrix = glm::scale(m_transformMatrix, m_scale);

		return m_transformMatrix;
	}

	void Mesh::Bind() const
	{
		m_vertexArray->Bind();
		if (m_texture)
		{
			m_texture->Bind(0);
		}
	}

	void Mesh::UnBind() const
	{
		m_vertexArray->UnBind();
		if (m_texture)
		{
			m_texture->UnBind();
		}
	}

}
