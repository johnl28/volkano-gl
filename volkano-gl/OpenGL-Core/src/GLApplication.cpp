
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

#include "GLApplication.h"
#include "Log.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include "Shader.h"
#include "ShaderProgram.h"


namespace glcore {

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	ShaderProgram* sp;

	void GlErrorCallback(int error_code, const char* description)
	{
		GLCORE_ERR("[OpenGL]: Error code %d. %s", error_code, description);
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			trans = glm::rotate(trans, 10.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case GLFW_KEY_S:
			trans = glm::rotate(trans, -10.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case GLFW_KEY_A:
			trans = glm::rotate(trans, 10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case GLFW_KEY_D:
			trans = glm::rotate(trans, -10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		default:
			return;
		}

		//sp->SetUniformMatrix4fv("u_View", view);
		sp->SetUniformMatrix4fv("u_Transform", trans);
	}

	void MouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		if (!sp) {
			return;
		}
		
		static double lastX = 0.0;
		static double lastY = 0.0;

		static GLfloat cameraVelocity = 0.02f;


		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			GLfloat x = 0.0f;
			GLfloat y = 0.0f;
			GLfloat z = 0.0f;

			if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			{
				x = lastX < xpos ? cameraVelocity : -cameraVelocity;
			}
			else if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
			{
				y = lastY < ypos ? -cameraVelocity : cameraVelocity;
			}
			else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			{
				z = lastY < ypos ? -cameraVelocity : cameraVelocity;
				z *= 5.0f;
			}
				

			view = glm::translate(view, glm::vec3(x, y, z));
		}

		lastX = xpos;
		lastY = ypos;

		sp->SetUniformMatrix4fv("u_View", view);
	}

	void SCROLL(GLFWwindow* window, double xoffset, double yoffset)
	{
		GLCORE_INFO("SCROLL");
		GLCORE_ERR("AAAAAAAAAAAAAAAAAAAA");
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
		if (m_window == nullptr)
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

		glEnable(GL_DEPTH_TEST);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glViewport(0, 0, m_width, m_height);

		glfwSetCursorPosCallback(m_window, MouseMove);
		glfwSetKeyCallback(m_window, KeyCallback);
		glfwSetScrollCallback(m_window, SCROLL);

		m_initialised = true;

		GLCORE_INFO("[GLApplication] GLFW Initialised");

		auto version = glGetString(GL_VERSION);
		GLCORE_INFO((char*)version);

	}

	void GLApplication::Run()
	{
		if (!m_initialised)
		{
			GLCORE_ERR("[GLApplication] Application loop cannot run if initialisation failed.");
			return;
		}

		Vertex vertices[] = {

			// front face
			{
				glm::vec3 { -1.0f, -1.0f, 1.0f },
				glm::vec2 { 0.0f, 1.0f },
			},

			{
				glm::vec3 { 1.0f, -1.0f, 1.0f },
				glm::vec2 { 1.0f, 1.0f },
			},

			{
				glm::vec3 { -1.0f, 1.0f, 1.0f },
				glm::vec2 { 0.0f, 0.0f },
			},

			{
				glm::vec3 { 1.0f, 1.0f, 1.0f },
				glm::vec2 { 1.0f, 0.0f }
			},


			// back face
			{
				glm::vec3 { -1.0f, -1.0f, -1.0f },
				glm::vec2 { 1.0f, 1.0f },
			},

			{
				glm::vec3 { 1.0f, -1.0f, -1.0f },
				glm::vec2 { 0.0f, 1.0f },

			},

			{
				glm::vec3 { -1.0f, 1.0f, -1.0f },
				glm::vec2 { 1.0f, 0.0f }
			},

			{
				glm::vec3 { 1.0f, 1.0f, -1.0f },
			
				glm::vec2 { 0.0f, 0.0f },
			},
		};



		GLuint indicies[] = {
			// front
			0, 1, 2,
			1, 3, 2,

			// back
			4, 5, 6,
			5, 7, 6,

			// left
			4, 0, 6,
			0, 2, 6,

			// right
			5, 1, 7,
			7, 3, 1,

			// top
			2, 3, 6,
			
		};

		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indicies, sizeof(indicies) / sizeof(GLuint));



		va.AddAttribute<GLfloat>(3);
		va.AddAttribute<GLfloat>(2);
		va.AddAttribute<GLfloat>(3);
		va.CreateAttribPointers();

		sp = new ShaderProgram();
		sp->LoadShaders("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");
		sp->Bind();

		Texture texture("assets/textures/uv_grid_opengl.jpg");
		texture.Bind(0);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		sp->SetUniformMatrix4fv("u_Transform", trans);

		glm::mat4 proj = glm::perspective(glm::radians(95.0f), (float)m_width /
			(float)m_height, 0.1f, 1000.0f);
		
		sp->SetUniformMatrix4fv("u_Projection", proj);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -50.1f));
		//view = glm::rotate(view, 30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		sp->SetUniformMatrix4fv("u_View", view);


		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

	}


	void GLApplication::SetSrollCallback(GLFWscrollfun func)
	{
		glfwSetScrollCallback(m_window, func);
	}
}
