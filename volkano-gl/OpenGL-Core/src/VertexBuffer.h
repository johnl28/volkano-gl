#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace glcore {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 textureCoord;
		glm::vec3 normals;
	};


	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
		~VertexBuffer();

		void Bind() const;
		void UnBind() const;

	private:
		GLuint m_bufferID = 0;
	};

}