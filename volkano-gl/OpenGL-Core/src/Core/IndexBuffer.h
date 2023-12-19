#pragma once
#include "glad/glad.h"

namespace glcore {

	class IndexBuffer
	{
	public:
		IndexBuffer(const GLuint* data, GLuint count);
		~IndexBuffer();

		void Bind() const;
		void UnBind() const;

		GLuint GetCount() const { return m_count; }

	private:
		GLuint m_bufferID = 0;
		GLuint m_count = 0;
	};

}
