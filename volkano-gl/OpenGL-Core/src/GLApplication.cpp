#include "GLApplication.h"


namespace glcore
{
	GLApplication::GLApplication(int width, int height, std::string title)
	{
		m_width = width;
		m_height = height;
		m_title = title;

		InitGLFW();
	}

	GLApplication::~GLApplication()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void GLApplication::InitGLFW()
	{
		printf("Init GLFW");

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

		if(m_window == nullptr)
		{
			printf("Failed to init GLFW window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize GLAD");
			return;
		}

		glViewport(0, 0, m_width, m_height);

		while (!glfwWindowShouldClose(m_window))
		{
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}


	}
}
