#pragma once
#include <memory>
#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "Camera.h"


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
		bool IsInitialised() const { return m_initialised; }

		void OnScroll(double xoffset, double yoffset);
		void OnCursorMove(double xpos, double ypos);
		void OnKeyInput(int key, int scancode, int action, int mods);

	private:
		void InitGLFW();
		void InitCamera();
		void InitInputEvents();


	private:
		int m_width = 0;
		int m_height = 0;

		bool m_initialised = false;
		std::string m_title = "";

		GLFWwindow* m_window = nullptr;

		std::unique_ptr<Camera> m_camera = nullptr;
	};

}

