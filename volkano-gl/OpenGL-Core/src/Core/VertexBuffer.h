#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace glcore {

	/**
	 * @brief Represents a single vertex in 3D space, including its position, texture coordinates, and normals.
	 */
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 textureCoord;
		glm::vec3 normals;
	};


	/**
	 * @brief Manages an OpenGL Vertex Buffer Object (VBO), handling its creation, binding, and unbinding.
	 * @param data Pointer to the vertex data.
	 * @param size Size of the vertex data in bytes.
	 * @param usage Hint for the intended use of the data (default is GL_STATIC_DRAW).
	 */
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;


		void Bind() const;
		void UnBind() const;

	private:
		GLuint m_bufferID = 0;
	};

}