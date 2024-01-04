#pragma once
#include <memory>
#include <string>
#include <map>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "Camera.h"
#include "Model.h"
#include "Core/ShaderProgram.h"


namespace glcore
{
	void GlScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void GlCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void GlKeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	class GLApplication
	{
	public:
		GLApplication(int width, int height, const std::string& title);
		~GLApplication();

		GLApplication(const GLApplication&) = delete;
		GLApplication& operator=(const GLApplication&) = delete;

		void Run();

		bool IsContextInitialised() const { return m_ctxInitialised; }

		Model* LoadModel(const std::string& modelPath);
		void AddModel(Model *model);

		
		ShaderProgram* GetShader(const std::string& shaderName) const;
		ShaderProgram* LoadShaders(const std::string& shaderName, const std::string& verShaderFile, const std::string& fragShaderFile);
		void AddShader(const std::string& shaderName, ShaderProgram* shader);


		void OnScroll(double xoffset, double yoffset);
		void OnCursorMove(double xpos, double ypos);
		void OnKeyInput(int key, int scancode, int action, int mods);

	private:
		void InitGLFW();
		void InitCamera();
		void InitInputEvents();
		void InitDefaultShaderProgram();

		void RenderModels();
		void CalculateFrameTime();

	private:
		int m_Width = 0;
		int m_Height = 0;

		double m_DeltaTime = 0.0f;
		bool m_ctxInitialised = false;
		std::string m_Title = "";

		GLFWwindow* m_Window = nullptr;

		std::unique_ptr<Camera> m_Camera = nullptr;

		std::vector<std::unique_ptr<Model>> m_Models;

		std::map<std::string, std::unique_ptr<ShaderProgram>> m_Shaders;
		std::unique_ptr<ShaderProgram> m_DefaultShader = nullptr;
	};

}

