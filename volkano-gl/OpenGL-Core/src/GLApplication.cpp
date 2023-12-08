#include "GLApplication.h"
#include "Log.h"

namespace glcore
{
	GLApplication::GLApplication(int width, int height, const std::string& title)
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

	void GLApplication::Run()
	{
		if (!m_initialised)
		{
			GLCORE_ERR("Application loop cannot run if initialisation failed.");
			return;
		}

		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

	}

	void GLApplication::InitGLFW()
	{
		if (glfwInit() != GLFW_TRUE)
		{
			GLCORE_ERR("Failed to initialise GLFW.");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

		if(m_window == nullptr)
		{
			GLCORE_ERR("Failed to create window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			GLCORE_ERR("Failed to initialize GLAD");
			return;
		}

		glViewport(0, 0, m_width, m_height);

		m_initialised = true;

		GLCORE_INFO("GLFW Initialised");
	}
}
