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
		Mesh(const Mesh&) = delete;
		Mesh& operator =(const Mesh&) = delete;

		void LoadTexture(const std::string& texturePath);
		const glm::mat4& GetTransformMatrix();

		void SetTexture(Texture* texture);

		GLuint GetIndexCount() const { return m_IndexBuffer->GetCount(); }
		GLuint GetID() const { return m_VertexArray->GetID(); }

		void SetPosition(const glm::vec3& newPosition);
		void SetRotation(const glm::vec3& newRotation);
		void SetScale(const glm::vec3& newScale);

		void Bind() const;
		void UnBind() const;

	private:
		void UpdateTransformMatrix();

	private:
		glm::mat4 m_TransformMatrix = glm::mat4(1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

	private:
		std::unique_ptr<VertexArray> m_VertexArray = nullptr;
		std::unique_ptr<VertexBuffer> m_VertexBuffer = nullptr;
		std::unique_ptr<IndexBuffer> m_IndexBuffer = nullptr;
		std::unique_ptr<Texture> m_Texture = nullptr;
	};

}
