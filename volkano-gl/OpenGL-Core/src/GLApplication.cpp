
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

#include "Log.h"
#include "GLApplication.h"

#include "Model.h"
#include "Core/Texture.h"
#include "Core/ShaderProgram.h"


namespace glcore {

	void GlErrorCallback(int error_code, const char* description)
	{
		GLCORE_ERR("[OpenGL]: Error code %d. %s", error_code, description);
	}

	GLApplication::GLApplication(int width, int height, const std::string& title)
	{
		m_Width = width;
		m_Height = height;
		m_title = title;

		InitGLFW();
		InitInputEvents();
		InitCamera();
		InitDefaultShaderProgram();
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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetErrorCallback(GlErrorCallback);


		m_window = glfwCreateWindow(m_Width, m_Height, m_title.c_str(), NULL, NULL);
		if (m_window == nullptr)
		{
			GLCORE_ERR("[GLApplication] Failed to create window");
			glfwTerminate();
			return;
		}


		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			GLCORE_ERR("[GLApplication] Failed to initialize GLAD");
			return;
		}

		glViewport(0, 0, m_Width, m_Height);
		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		auto version = glGetString(GL_VERSION);
		GLCORE_INFO("%s", (char*)version);

		GLCORE_INFO("[GLApplication] GLFW Initialised");

		m_ctxInitialised = true;
	}

	void GLApplication::InitCamera()
	{
		if (!m_ctxInitialised)
		{
			return;
		}

		Projection projection = {
			ProjectionType::PERSPECTIVE_PROJECTION,

			45.0f,

			(float)m_Width / (float)m_Height, 
			0.10f, 
			1000.0f
		};

		m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 200.0f), projection);

		GLCORE_INFO("[GLApplication] Camera initiliased");
	}

	void GLApplication::InitInputEvents()
	{
		if (!m_ctxInitialised)
		{
			return;
		}

		glfwSetKeyCallback(m_window, GlKeyInputCallback);
		glfwSetScrollCallback(m_window, GlScrollCallback);
		glfwSetCursorPosCallback(m_window, GlCursorPosCallback);
	}

	void GLApplication::InitDefaultShaderProgram()
	{
		if (!m_ctxInitialised)
		{
			return;
		}

		m_shaderProgram = std::make_unique<ShaderProgram>();
		m_shaderProgram->LoadShaders("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");
		if (!m_shaderProgram->IsLinked())
		{
			return;
		}

		GLCORE_INFO("[GLApplication] Default shader program initialised");
	}

	void GLApplication::Run()
	{
		if (!m_ctxInitialised)
		{
			GLCORE_ERR("[GLApplication] Application loop cannot run if initialisation failed.");
			return;
		}

		m_LastFrameTime = glfwGetTime();

		Texture texture("assets/textures/debug/512x512/Gray/Prototype_Grid_Gray_07-512x512.png");
		texture.Bind(0);

		auto model = new Model();
		model->Load("assets/models/monkey.obj");
		model->Scale(glm::vec3(0.7f));
		//model->Rotate(glm::vec3(-90.0f, 0.0f, 0.0f));
		model->Move(glm::vec3(0.0f, -0.6f, 0.0f));

		auto light = new Model();
		light->Load("assets/models/sphere.obj");
		light->Move(glm::vec3(1.2f, 1.0f, 2.0f));
		light->Scale(glm::vec3(0.1f));
		GLCORE_INFO("Light Pos %f %f %f",  light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
		//light->Rotate(glm::vec3(-70.0f, 0.0f, 0.0f));

		auto clearColor = glm::vec3(0, 104, 145) / 255.0f;
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);



		m_shaderProgram->SetUniform3f("u_LightColor", 1.0f, 1.0f, 1.0f);

		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float currentFrame = glfwGetTime();
			float deltaTime = currentFrame - m_LastFrameTime;
			m_LastFrameTime = currentFrame;

			if (glfwGetKey(m_window, GLFW_KEY_T) == GLFW_PRESS)
			{
				light->Move(glm::vec3(-0.03, 0.0f, 0.0f));
			}
			if (glfwGetKey(m_window, GLFW_KEY_Y) == GLFW_PRESS)
			{
				light->Move(glm::vec3(0.03, 0.0f, 0.0f));
			}
			if (glfwGetKey(m_window, GLFW_KEY_U) == GLFW_PRESS)
			{
				light->Move(glm::vec3(0.0f, -0.03f, 0.0f));
			}
			if (glfwGetKey(m_window, GLFW_KEY_J) == GLFW_PRESS)
			{
				light->Move(glm::vec3(0.0f, 0.03f, 0.0f));
			}


			model->Rotate(glm::vec3(0.0f, 20.0f * deltaTime, 0.0f));

			m_shaderProgram->Bind();
			if (m_camera->IsViewMatrixDirty())
			{
				m_shaderProgram->SetUniformMatrix4fv("u_View", m_camera->GetViewMatrix());
			}

			if (m_camera->IsProjectionMatrixDirty())
			{
				m_shaderProgram->SetUniformMatrix4fv("u_Projection", m_camera->GetProjectionMatrix());
			}

			m_shaderProgram->SetUniformVec3("u_ViewPos", m_camera->GetPosition());
			m_shaderProgram->SetUniformVec3("u_LightPositon", light->GetPosition());
			m_camera->Update(deltaTime);
			model->Render(m_shaderProgram.get());
			light->Render(m_shaderProgram.get());

			RenderMeshes();

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

	}

	void GLApplication::RenderMeshes()
	{
		for (auto& it : m_meshVec)
		{
			RenderMesh(it.get());
		}
	}

	void GLApplication::RenderMesh(Mesh* mesh)
	{
		if (!mesh)
		{
			return;
		}

		mesh->Bind();
		m_shaderProgram->SetUniformMatrix4fv("u_Transform", mesh->GetTransformMatrix());

		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

	void GLApplication::AddMesh(Mesh* mesh)
	{
		m_meshVec.push_back(std::unique_ptr<Mesh>(mesh));
	}

	void GLApplication::OnScroll(double xoffset, double yoffset)
	{
	}

	void GLApplication::OnCursorMove(double xpos, double ypos)
	{

		static bool firstMouse = true;
		static float lastX = 0, lastY = 0;
		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (firstMouse)
			{
				glfwSetCursorPos(m_window, m_Width / 2, m_Height / 2);
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos;
			lastX = xpos;
			lastY = ypos;

			float sensitivity = 0.005f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;
			if (xoffset > 1.0f || yoffset > 1.0f)
			{
				return;
			}

			

			//if (pitch > 89.0f)
			//	pitch = 89.0f;
			//if (pitch < -89.0f)
			//	pitch = -89.0f;

			GLCORE_INFO("Pitch %f, Yaw %f", xoffset, yoffset);

			m_camera->Yaw(xoffset);
			m_camera->Pitch(yoffset);
		}
		else if(glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstMouse = true;
		}




	}

	void GLApplication::OnKeyInput(int key, int scancode, int action, int mods)
	{
		switch (key)
		{
			case GLFW_KEY_W:
			{
				m_camera->MoveZ(1.0f);
				break;
			}

			case GLFW_KEY_S:
			{
				m_camera->MoveZ(-1.0f);
				break;
			}

			case GLFW_KEY_A:
			{
				m_camera->MoveX(1.0f);
				break;
			}

			case GLFW_KEY_D:
			{
				m_camera->MoveX(-1.0f);
				break;
			}
			case GLFW_KEY_Q:
			{
				m_camera->Yaw(0.02f);
				break;
			}
		}

	}


	void GlScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		// Assign glApp only on the first call
		static auto glApp = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));
		if (!glApp)
		{
			GLCORE_ERR("[GlScrollCallback] Window app pointer null.");
			return;
		}

		glApp->OnScroll(xoffset, yoffset);
	}

	void GlCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		static auto glApp = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));
		if (!glApp)
		{
			GLCORE_ERR("[GlCursorPosCallback] Window app pointer null.");
			return;
		}

		glApp->OnCursorMove(xpos, ypos);
	}

	void GlKeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		static auto glApp = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));
		if (!glApp)
		{
			GLCORE_ERR("[GlCursorPosCallback] Window app pointer null.");
			return;
		}

		glApp->OnKeyInput(key, scancode, action, mods);
	}

}
