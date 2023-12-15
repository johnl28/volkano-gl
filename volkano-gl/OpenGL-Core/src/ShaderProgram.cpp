#include "glm/gtc/type_ptr.hpp"

#include "ShaderProgram.h"
#include "Log.h"

namespace glcore {

	ShaderProgram::ShaderProgram()
	{
		m_programId = glCreateProgram();
	}

	void ShaderProgram::LoadShaders(const std::string& verShaderFilePath, const std::string& fragShaderFilePath)
	{
		Shader vertexShader(verShaderFilePath, GL_VERTEX_SHADER);
		vertexShader.Compile();

		Shader fragmentShader(fragShaderFilePath, GL_FRAGMENT_SHADER);
		fragmentShader.Compile();

		AttachShader(&vertexShader);
		AttachShader(&fragmentShader);
		LinkProgram();
	}

	void ShaderProgram::AttachShader(Shader* shader)
	{
		if (!shader)
		{
			GLCORE_ERR("[Shader Program] Failed to attach shader to program %d, null pointer.", m_programId);
			return;
		}
		else if (!shader->IsCompiled())
		{
			GLCORE_ERR("[Shader Program] Failed to attach uncompiled shader to program. Program ID %d, Shader file: %s", m_programId, shader->GetFilePath().c_str());
			return;
		}

		glAttachShader(m_programId, shader->GetID());
	}

	void ShaderProgram::LinkProgram()
	{
		glLinkProgram(m_programId);

		GLint success = 0;

		glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			char errBuff[500];
			glGetProgramInfoLog(m_programId, sizeof(errBuff), nullptr, errBuff);

			GLCORE_ERR("[Shader Program] Failed to link shader program with id %d. Error: %s", m_programId, errBuff);
			return;
		}

		m_linked = true;
		GLCORE_INFO("[Shader Program] Program %d linked", m_programId);
	}

	void ShaderProgram::Bind() const
	{
		glUseProgram(m_programId);
	}

	void ShaderProgram::Unbind() const
	{
		glUseProgram(0);
	}

	void ShaderProgram::SetUniform1i(const std::string& uniform, GLint v0)
	{
		glUniform1i(GetUniformLocation(uniform), v0);
	}

	void ShaderProgram::SetUniform4f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		glUniform4f(GetUniformLocation(uniform), v0, v1, v2, v3);
	}

	void ShaderProgram::SetUniform3f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		glUniform3f(GetUniformLocation(uniform), v0, v1, v2);
	}

	void ShaderProgram::SetUniformMatrix4fv(const std::string& uniform, glm::mat4 matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLuint ShaderProgram::GetUniformLocation(const std::string& uniform)
	{
		auto it = m_unifromLocation.find(uniform);
		if (it != m_unifromLocation.end())
		{
			return it->second;
		}

		auto location = glGetUniformLocation(GetID(), uniform.c_str());
		if (location == -1)
		{
			GLCORE_WARN("[Shader Program] Shader unfirom %s not found", uniform.c_str());
		}

		m_unifromLocation[uniform] = location;
		return location;
	}


}