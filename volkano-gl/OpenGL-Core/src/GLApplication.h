#pragma once
#include <memory>
#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "Camera.h"
#include "Mesh.h"
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
		void AddMesh(Mesh *mesh);

		void OnScroll(double xoffset, double yoffset);
		void OnCursorMove(double xpos, double ypos);
		void OnKeyInput(int key, int scancode, int action, int mods);

	private:
		void InitGLFW();
		void InitCamera();
		void InitInputEvents();
		void InitDefaultShaderProgram();

		void RenderMeshes();
		void RenderMesh(Mesh* mesh);

	private:
		int m_width = 0;
		int m_height = 0;

		float m_LastFrameTime = 0.0f;
		bool m_ctxInitialised = false;
		std::string m_title = "";

		GLFWwindow* m_window = nullptr;

		std::vector<std::unique_ptr<Mesh>> m_meshVec;

		std::unique_ptr<Camera> m_camera = nullptr;

		// Short-term 
		// todo: Create a map to store multiple shaders used by different materials
		std::unique_ptr<ShaderProgram> m_shaderProgram = nullptr;
	};

}

