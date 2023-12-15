#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_arrayID);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_arrayID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_arrayID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::CreateAttribPointers() const
{
	size_t offset = 0;

	for (int i = 0; i < m_attributes.size(); i++)
	{
		const auto& attr = m_attributes[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attr.count, attr.type, attr.normalized, (GLsizei)m_stride, (const void*) offset);

		offset = attr.count * VertexAttribute::GetAttrSize(attr.type);
	}
}

template<>
void VertexArray::AddAttribute<GLfloat>(GLint count)
{
	m_attributes.push_back({ GL_FLOAT, GL_FALSE, count });
	m_stride += sizeof(GLfloat) * count;
}


// todo: Fix issue with vec2, 3, 4 struct
template<>
void VertexArray::AddAttribute<glm::vec2>(GLint count)
{
	m_attributes.push_back({ GL_FLOAT_VEC2, GL_FALSE, count });
	m_stride += sizeof(glm::vec2) * count;
}

template<>
void VertexArray::AddAttribute<glm::vec3>(GLint count)
{
	m_attributes.push_back({ GL_FLOAT_VEC2, GL_FALSE, count });
	m_stride += sizeof(glm::vec3) * count;
}

template<>
void VertexArray::AddAttribute<glm::vec4>(GLint count)
{
	m_attributes.push_back({ GL_FLOAT_VEC2, GL_FALSE, count });
	m_stride += sizeof(glm::vec4) * count;
}


