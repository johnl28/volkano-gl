
#include "glm/gtc/matrix_transform.hpp"
#include "GLApplication.h"
#include "Log.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include "Shader.h"
#include "ShaderProgram.h"

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
			GLCORE_ERR("[GLApplication] Application loop cannot run if initialisation failed.");
			return;
		}

		glm::vec2 positions[] = {
			glm::vec2 { -0.5f, -0.5f }, // pos
			glm::vec2 { 0.0f, 1.0f }, // tex

			glm::vec2 { 0.5f, -0.5f }, // pos
			glm::vec2 { 1.0f, 1.0f }, // tex

			glm::vec2 { -0.5f, 0.5f }, // pos
			glm::vec2 { 0.0f, 0.0f }, // tex

			glm::vec2 { 0.5f, 0.5f }, // pos
			glm::vec2 { 1.0f, 0.0f }  // tex

		};

		GLuint indicies[] = {
			0, 1, 2,
			1, 3, 2
		};

		VertexArray va;
		VertexBuffer vb(positions, sizeof(positions));
		IndexBuffer ib(indicies, 6);


		va.AddAttribute<GLfloat>(2);
		va.AddAttribute<GLfloat>(2);
		va.CreateAttribPointers();

		ShaderProgram program;
		program.LoadShaders("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");
		program.Bind();

		Texture texture("assets/textures/brick_wall2.jpg");
		texture.Bind(0);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(2.0, 2.0, 2.0));
		program.SetUniformMatrix4fv("u_Transform", trans);

		
		float r = 0.0f;
		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			//
			//r += 0.01f;
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

	}


	void GLApplication::InitGLFW()
	{
		if (glfwInit() != GLFW_TRUE)
		{
			GLCORE_ERR("[GLApplication] Failed to initialise GLFW.");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetErrorCallback(GlErrorCallback);


		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		if(m_window == nullptr)
		{
			GLCORE_ERR("[GLApplication] Failed to create window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			GLCORE_ERR("[GLApplication] Failed to initialize GLAD");
			return;
		}

		glViewport(0, 0, m_width, m_height);

		m_initialised = true;

		GLCORE_INFO("[GLApplication] GLFW Initialised");

		auto version = glGetString(GL_VERSION);
		GLCORE_INFO((char*)version);

	}

	void GLApplication::SetSrollCallback(GLFWscrollfun func)
	{
		glfwSetScrollCallback(m_window, func);
	}
}
