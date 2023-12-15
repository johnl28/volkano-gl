#include "VertexBuffer.h"

namespace glcore {

	VertexBuffer::VertexBuffer(const void* data, size_t size, GLenum usage)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_bufferID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	void VertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}