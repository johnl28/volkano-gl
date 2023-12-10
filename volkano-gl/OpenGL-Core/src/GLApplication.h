#pragma once
#include <memory>
#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"


namespace glcore
{
	class GLApplication
	{
	public:
		GLApplication(int width, int height, const std::string& title);
		~GLApplication();

		GLApplication(const GLApplication&) = delete;
		GLApplication& operator=(const GLApplication&) = delete;

		void Run();

		bool IsInitialised() { return m_initialised; }

	private:
		void InitGLFW();

	private:

		int m_width = 0;
		int m_height = 0;

		bool m_initialised = false;
		std::string m_title = "";

		GLFWwindow* m_window = nullptr;
	};
}

