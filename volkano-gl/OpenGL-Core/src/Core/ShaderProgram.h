#pragma once
#include <unordered_map>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Shader.h"


namespace glcore {


	/**
	 * @brief Manages an OpenGL shader program, encapsulating shader attachment, linking, and uniform management.
	 */
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		void LoadShaders(const std::string& vertexShader, const std::string& fragmentShader);

		void AttachShader(Shader* shader);
		void LinkProgram();

		void Bind() const;
		void Unbind() const;

		void SetUniformVec3(const std::string& uniform, const glm::vec3& val);
		void SetUniformVec4(const std::string& uniform, const glm::vec4& val);

		void SetUniform1i(const std::string& uniform, GLint v0);
		void SetUniform1f(const std::string& uniform, GLfloat v0);
		void SetUniform4f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		void SetUniform3f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2);

		void SetUniformMatrix4fv(const std::string& uniform, glm::mat4 matrix);

		bool IsLinked() const { return m_linked; }
		GLuint GetID() const { return m_programId; }

	private:
		GLuint GetUniformLocation(const std::string& uniform);

	private:
		std::unordered_map<std::string, GLint> m_unifromLocation;

		GLuint m_programId = 0;

		bool m_linked = false;
	};

}