#pragma once
#include <unordered_map>

#include "glad/glad.h"

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();

	void AttachShader(Shader* shader);
	void LinkProgram();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& uniform, GLint v0);
	void SetUniform4f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniform3f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2);

	GLuint GetID() const { return m_programId; }

private:
	GLuint GetUniformLocation(const std::string& uniform);

private:
	std::unordered_map<std::string, GLint> m_unifromLocation;

	GLuint m_programId = 0;

	bool m_linked = false;
};

