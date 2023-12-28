#include "Mesh.h"

#include "glm/gtc/matrix_transform.hpp"

namespace glcore {

	Mesh::Mesh(const void* vertexData, size_t vertexDataSize, const GLuint* indexData, GLuint indexCount)
	{
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertexData, vertexDataSize);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indexData, indexCount);

		m_VertexArray->AddAttribute<GLfloat>(3);
		m_VertexArray->AddAttribute<GLfloat>(2);
		m_VertexArray->AddAttribute<GLfloat>(3);
		m_VertexArray->CreateAttribPointers();

		m_VertexArray->UnBind();
		m_VertexBuffer->UnBind();
		m_IndexBuffer->UnBind();
	}

	void Mesh::LoadTexture(const std::string& texturePath)
	{
		auto texture = new Texture(texturePath);
		if (!texture->IsLoaded())
		{
			delete texture;
			return;
		}

		m_Texture = std::unique_ptr<Texture>(texture);
	}

	const glm::mat4& Mesh::GetTransformMatrix()
	{
		return m_TransformMatrix;
	}

	void Mesh::SetPosition(const glm::vec3& newPosition)
	{
		m_Position = newPosition;
		UpdateTransformMatrix();
	}

	void Mesh::SetRotation(const glm::vec3& newRotation)
	{
		m_Rotation = newRotation;
		UpdateTransformMatrix();
	}

	void Mesh::SetScale(const glm::vec3& newScale)
	{
		m_Scale = newScale;
		UpdateTransformMatrix();
	}

	void Mesh::UpdateTransformMatrix()
	{
		m_TransformMatrix = glm::mat4(1.0f);
		m_TransformMatrix = glm::translate(m_TransformMatrix, m_Position);
		m_TransformMatrix = glm::scale(m_TransformMatrix, m_Scale);

		m_TransformMatrix = glm::rotate(m_TransformMatrix, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		m_TransformMatrix = glm::rotate(m_TransformMatrix, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		m_TransformMatrix = glm::rotate(m_TransformMatrix, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void Mesh::Bind() const
	{
		m_VertexArray->Bind();
		if (m_Texture)
		{
			m_Texture->Bind(0);
		}
	}

	void Mesh::UnBind() const
	{
		m_VertexArray->UnBind();
		if (m_Texture)
		{
			m_Texture->UnBind();
		}
	}

}
