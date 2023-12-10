#include "GLApplication.h"
#include "Log.h"

namespace glcore
{
	void GlErrorCallback(int error_code, const char* description)
	{
		GLCORE_ERR("[OpenGL]: Error code %d. %s", error_code, description);
	}


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

		float positions[6] = {
			-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f
		};

		GLuint buffer;

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		glEnableVertexAttribArray(0);


		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
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

		glfwSetErrorCallback(GlErrorCallback);


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

		auto version = glGetString(GL_VERSION);
		GLCORE_INFO((char*)version);

	}
}
