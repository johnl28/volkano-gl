#pragma once
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"


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


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

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

