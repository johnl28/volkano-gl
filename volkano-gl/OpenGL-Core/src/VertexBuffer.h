#pragma once
#include "glad/glad.h"

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
