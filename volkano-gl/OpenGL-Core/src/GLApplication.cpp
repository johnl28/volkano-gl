
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

#include "Mesh.h"

namespace glcore {

	void GlErrorCallback(int error_code, const char* description)
	{
		GLCORE_ERR("[OpenGL]: Error code %d. %s", error_code, description);
	}

	void GlScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		auto glApp = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));
		if (!glApp)
		{
			GLCORE_ERR("[GlScrollCallback] Window app pointer null.");
			return;
		}

		glApp->OnScroll(xoffset, yoffset);
	}

	void GlCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		auto glApp = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));
		if (!glApp)
		{
			GLCORE_ERR("[GlCursorPosCallback] Window app pointer null.");
			return;
		}

		glApp->OnCursorMove(xpos, ypos);
	}

	GLApplication::GLApplication(int width, int height, const std::string& title)
	{
		m_width = width;
		m_height = height;
		m_title = title;

		InitGLFW();
		InitCamera();
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
		glfwSetWindowUserPointer(m_window, this);

		glfwSetScrollCallback(m_window, GlScrollCallback);
		glfwSetCursorPosCallback(m_window, GlCursorPosCallback);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			GLCORE_ERR("[GLApplication] Failed to initialize GLAD");
			return;
		}

		glViewport(0, 0, m_width, m_height);

		glEnable(GL_DEPTH_TEST);


		m_initialised = true;

		auto version = glGetString(GL_VERSION);
		GLCORE_INFO("%s", (char*)version);

		GLCORE_INFO("[GLApplication] GLFW Initialised");

	}

	void GLApplication::InitCamera()
	{
		Projection projection = {
			ProjectionType::PERSPECTIVE_PROJECTION,
			95.0f, 
			(float)m_width / (float)m_height, 
			0.1f, 
			1000.0f
		};

		m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, -120.0f), glm::vec3(0.0f), projection);

		GLCORE_INFO("[GLApplication] Camera initiliased");
	}

	void GLApplication::OnScroll(double xoffset, double yoffset)
	{
		m_camera->Move(glm::vec3(0.0f, 0.0f, 5.0f * yoffset));
	}

	void GLApplication::OnCursorMove(float xpos, float ypos)
	{
		static float lasty = 0;

		float yaw = lasty < ypos ? 10.1f : -10.1f;
		m_camera->Yaw(yaw);

		lasty = ypos;
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

		Mesh mesh(vertices, sizeof(vertices), indicies, sizeof(indicies) / sizeof(GLuint));
		mesh.Bind();

		auto shader = new ShaderProgram();
		shader->LoadShaders("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");
		shader->Bind();

		Texture texture("assets/textures/uv_grid_opengl.jpg");
		texture.Bind(0);


		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shader->Bind();
			if (m_camera->IsViewMatrixDirty())
			{
				shader->SetUniformMatrix4fv("u_View", m_camera->GetViewMatrix());
			}

			if (m_camera->IsProjectionMatrixDirty())
			{
				shader->SetUniformMatrix4fv("u_Projection", m_camera->GetProjectionMatrix());
			}

			shader->SetUniformMatrix4fv("u_Transform", mesh.GetTransformMatrix());
			glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

	}


}
