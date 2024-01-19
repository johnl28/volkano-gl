#pragma once
#include "glad/glad.h"

namespace glcore {

	/**
	 * @brief Manages an OpenGL index buffer, used for efficient rendering of vertex data.
	 * @param data Pointer to the index data array.
	 * @param count The number of indices in the data array.
	 */
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
