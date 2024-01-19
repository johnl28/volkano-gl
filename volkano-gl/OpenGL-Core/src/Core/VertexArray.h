#pragma once
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace glcore {

	/**
	 * @brief Represents a single vertex attribute in a Vertex Array, including its type, count, and normalization flag.
	 * Provides a static method to get the size of different OpenGL data types used in vertex attributes.
	 */
	struct VertexAttribute
	{
		GLenum type;
		GLboolean normalized;
		GLint count;


		static size_t GetAttrSize(GLenum type)
		{
			switch (type)
			{
			case GL_FLOAT:
				return sizeof(GLfloat);

			case GL_FLOAT_VEC2:
				return sizeof(glm::vec2);

			case GL_FLOAT_VEC3:
				return sizeof(glm::vec3);

			case GL_FLOAT_VEC4:
				return sizeof(glm::vec4);

			default:
				assert(false);
			}

			return 0;
		}
	};

	/**
	 * @brief Manages an OpenGL Vertex Array Object (VAO), handling binding, unbinding, and attribute configuration.
	 */
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		GLuint GetID() const { return m_arrayID; }
		void Bind() const;
		void UnBind() const;

		void CreateAttribPointers() const;

		template<class T>
		void AddAttribute(GLint count);

		template<>
		void AddAttribute<GLfloat>(GLint count);

		template<>
		void AddAttribute<glm::vec2>(GLint count);

		template<>
		void AddAttribute<glm::vec3>(GLint count);

		template<>
		void AddAttribute<glm::vec4>(GLint count);

	private:
		GLuint m_arrayID = 0;

		size_t m_stride = 0;

		std::vector<VertexAttribute> m_attributes;

	};

}