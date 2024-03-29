#pragma once
#include <vector>
#include <string>

#include "glad/glad.h"

namespace glcore {

	/**
	 * @brief Represents a single OpenGL shader, handling its creation, compilation, and management.
	 * @param file Path to the shader source file.
	 * @param shaderType The type of shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
	 */
	class Shader
	{
	public:
		Shader(const std::string& file, GLenum shaderType);
		~Shader();

		void Compile();


		GLint GetID() const { return m_shaderId; }
		GLenum GetType() const { return m_shaderType; }
		const std::string& GetFilePath() const { return m_shaderFilePath; }

		bool IsCompiled() const { return m_compiled; }

	private:
		void ReadShaderFile();

	private:
		GLuint m_shaderId = 0;
		GLenum m_shaderType = 0;

		std::string m_shaderFilePath = "";
		std::string m_shaderCode = "";

		bool m_compiled = false;
	};


}