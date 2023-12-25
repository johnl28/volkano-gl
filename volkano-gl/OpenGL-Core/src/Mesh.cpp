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

	void Mesh::LoadTexture(const std::string& texturePath)
	{
		auto texture = new Texture(texturePath);
		m_texture = 
	}

	const glm::mat4& Mesh::GetTransformMatrix()
	{
		m_transformMatrix = glm::mat4(1.0f);
		m_transformMatrix = glm::translate(m_transformMatrix, m_Position);
		m_transformMatrix = glm::scale(m_transformMatrix, m_scale);

		m_transformMatrix = glm::rotate(m_transformMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		m_transformMatrix = glm::rotate(m_transformMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		m_transformMatrix = glm::rotate(m_transformMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

		return m_transformMatrix;
	}

	void Mesh::Move(glm::vec3 velocity)
	{
		m_Position += velocity;
	}

	void Mesh::Rotate(glm::vec3 deg)
	{
		m_rotation += deg;
	}

	void Mesh::Scale(glm::vec3 scale)
	{
		m_scale = scale;
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
