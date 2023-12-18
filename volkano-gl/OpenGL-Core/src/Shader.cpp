#include <fstream>
#include <iostream>
#include <sstream>

#include "Log.h"
#include "Shader.h"


namespace glcore {


	Shader::Shader(const std::string& filePath, GLenum shaderType)
	{
		m_shaderType = shaderType;
		m_shaderFilePath = filePath;

		m_shaderId = glCreateShader(m_shaderType);

		ReadShaderFile();
	}

	Shader::~Shader()
	{
		glDeleteShader(m_shaderId);
	}

	void Shader::ReadShaderFile()
	{
		std::ifstream file(m_shaderFilePath, std::ios::binary);
		std::stringstream shaderStream;

		if (!file.is_open())
		{
			GLCORE_ERR("[Shader] Failed to open shader file %s", m_shaderFilePath.c_str());
			return;
		}

		shaderStream << file.rdbuf();
		file.close();

		m_shaderCode = shaderStream.str();
	}

	void Shader::Compile()
	{
		if (m_shaderCode.empty())
		{
			GLCORE_ERR("[Shader] Failed to compile empty shader file %s.", m_shaderFilePath.c_str());
			return;
		}


		const char* source = m_shaderCode.c_str();

		glShaderSource(m_shaderId, 1, &source, NULL);
		glCompileShader(m_shaderId);

		GLint success = 0;
		glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(m_shaderId, 512, nullptr, infoLog);

			GLCORE_ERR("[Shader] Failed to compile shader file %s. \n Error: %s", m_shaderFilePath.c_str(), infoLog);
			return;
		}

		GLCORE_INFO("[Shader] shader %s compiled", m_shaderFilePath.c_str());
		m_compiled = true;
	}


}