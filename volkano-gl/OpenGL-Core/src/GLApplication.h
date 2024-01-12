#pragma once
#include <memory>
#include <string>
#include <map>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "UI.h"
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

		bool IsContextInitialised() const { return m_CtxInitialised; }

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
		void InitUI();
		void InitInputEvents();
		void InitDefaultShaderProgram();

		void RenderModels();
		void CalculateFrameTime();

		// Camera
		void UpdateCameraPosition();
		void UpdateCameraRotation(double xpos, double ypos);
		

	private:
		int m_Width = 0;
		int m_Height = 0;
		std::string m_Title = "";

		bool m_CtxInitialised = false;

		double m_DeltaTime = 0.0f;

		GLFWwindow* m_Window = nullptr;

		std::unique_ptr<UI> m_UI = nullptr;
		std::unique_ptr<Camera> m_Camera = nullptr;

		std::vector<std::unique_ptr<Model>> m_Models;

		std::unique_ptr<ShaderProgram> m_DefaultShader = nullptr;
		std::map<std::string, std::unique_ptr<ShaderProgram>> m_Shaders;
	};

}

