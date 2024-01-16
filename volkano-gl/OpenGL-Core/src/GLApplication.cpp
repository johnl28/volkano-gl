
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

#include "imgui/imgui.h"

#include "Renderer.h"
#include "Log.h"
#include "GLApplication.h"
#include "Skybox.h"
#include "ParticleSystem.h"

#include "GlRandom.h"

#include "Model.h"
#include "Core/Texture.h"
#include "Core/ShaderProgram.h"
#include "Core/CubeMap.h"

namespace glcore {

	void GlErrorCallback(int error_code, const char* description)
	{
		GLCORE_ERR("[OpenGL]: Error code %d. %s", error_code, description);
	}

	GLApplication::GLApplication(int width, int height, const std::string& title)
	{
		m_Width = width;
		m_Height = height;
		m_Title = title;

		InitGLFW();
		InitInputEvents();
		InitUI();
		InitCamera();
		InitDefaultShaders();
		InitDirectionalLight();
		InitSkybox();
	}

	GLApplication::~GLApplication()
	{
		m_UI->Destroy();

		glfwDestroyWindow(m_Window);
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


		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);

		if (m_Window == nullptr)
		{
			GLCORE_ERR("[GLApplication] Failed to create window");
			glfwTerminate();
			return;
		}


		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);
		glfwSetWindowUserPointer(m_Window, this);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			GLCORE_ERR("[GLApplication] Failed to initialize GLAD");
			return;
		}

		glViewport(0, 0, m_Width, m_Height);
		glEnable(GL_DEPTH_TEST);


		auto version = glGetString(GL_VERSION);
		GLCORE_INFO("%s", (char*)version);

		GLCORE_INFO("[GLApplication] GLFW Initialised");

		m_CtxInitialised = true;
	}

	void GLApplication::InitCamera()
	{
		if (!m_CtxInitialised)
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

		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 20.0f, 10.0f), projection);

		GLCORE_INFO("[GLApplication] Camera initiliased");
	}

	void GLApplication::InitUI()
	{
		m_UI = std::make_unique<UI>();
		m_UI->Initialise(m_Window);
	}

	void GLApplication::InitInputEvents()
	{
		if (!m_CtxInitialised)
		{
			return;
		}

		glfwSetKeyCallback(m_Window, GlKeyInputCallback);
		glfwSetScrollCallback(m_Window, GlScrollCallback);
		glfwSetCursorPosCallback(m_Window, GlCursorPosCallback);
		glfwSetWindowSizeCallback(m_Window, GlWindowResizeCallBack);
	}

	void GLApplication::InitDefaultShaders()
	{
		if (!m_CtxInitialised)
		{
			return;
		}

		auto modelShader = LoadShaders("modelShader", "assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");
		auto lampShader = LoadShaders("lampShader", "assets/shaders/lamp_vert.glsl", "assets/shaders/lamp_frag.glsl");

		if (!lampShader->IsLinked() || !modelShader->IsLinked())
		{
			GLCORE_ERR("[Application] Failed to load default shaders.");
			abort();
			return;
		}

		modelShader->Bind();
		modelShader->SetUniform1f("u_AmbientLight", m_AmbientLight);
		modelShader->SetUniform1f("u_SpecularStrength", m_SpecularStrength);

		GLCORE_INFO("[GLApplication] Default shaders initialised");
	}

	void GLApplication::InitSkybox()
	{
		std::vector<std::string> textures = { 
			"assets/textures/skybox/right.jpg",
			"assets/textures/skybox/left.jpg",
			"assets/textures/skybox/top.jpg",
			"assets/textures/skybox/bottom.jpg",
			"assets/textures/skybox/front.jpg",
			"assets/textures/skybox/back.jpg" 
		};

		auto cubeMap = new CubeMap(textures);
		if (!cubeMap->IsLoaded())
		{
			GLCORE_ERR("[Application] Failed to load skybox textures.");
			return;
		}

		auto shader = LoadShaders("skybox", "assets/shaders/skybox_vert.glsl", "assets/shaders/skybox_frag.glsl");
		if (!shader->IsLinked())
		{
			GLCORE_ERR("[Application] Failed to load skybox shaders.");
			return;
		}

		auto model = new Model();
		model->Load("assets/models/shapes/cube.fbx");
		if (!model->IsLoaded())
		{
			GLCORE_ERR("[Application] Failed to load skybox model.");
			return;
		}

		auto skybox = new Skybox(model, cubeMap, shader);
		m_Skybox = std::unique_ptr<Skybox>(skybox);
	}


	void GLApplication::Run()
	{
		if (!m_CtxInitialised)
		{
			GLCORE_ERR("[GLApplication] Application loop cannot run if initialisation failed.");
			return;
		}

		m_DeltaTime = glfwGetTime();
		

		glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0f);

		auto texture = Texture("assets/textures/GreyboxTextures/greybox_grey_grid.png");
		texture.Bind();

		auto modelShader = GetShader("modelShader");
		auto &renderer = Renderer::Get();

		auto model = new Model();
		model->Load("assets/models/shapes/cube.fbx");

		ParticleSystem particleSystem(model);
		particleSystem.SetPosition(glm::vec3(0, 5.0f, -50.0f));


			

		while (!glfwWindowShouldClose(m_Window))
		{
			//if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
			{
				Particle particle;
				particle.LifeTime = 1.0f;
				particle.Velocity = glm::vec3(Random::Float(-0.3f, 0.3f), 1.0f, Random::Float(-0.3f, 0.3f));
				particleSystem.Emit(particle);
			}


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_UI->NewFrame();

			glfwPollEvents();
			CalculateFrameTime();

			UpdateCameraPosition();

			particleSystem.OnUpdate(m_DeltaTime);
			particleSystem.OnRender(m_Camera.get());

			for (auto &model : m_Models)
			{
				auto shader = model->GetShader() ? model->GetShader() : modelShader;
				renderer.RenderModel(model.get(), m_Camera.get(), shader, m_DirectionalLight.get());
			}

			m_Camera->Update(m_DeltaTime);

			if (m_Skybox)
			{
				renderer.RenderSkybox(m_Skybox.get(), m_Camera.get());
			}

			OnUISettings();

			m_UI->Render();

			glfwSwapBuffers(m_Window);
		}

	}


	void GLApplication::OnUISettings()
	{

		static auto cameraSpeed = m_Camera->GetSpeed();
		static auto cameraFOV = m_Camera->GetFOV();

		static auto lightColor = m_DirectionalLight->GetColor();
		static auto lightPos = m_DirectionalLight->GetPosition();

		static bool drawLines = false;
		static bool skyBox = m_Skybox ? m_Skybox->IsEnabled(): false;

		ImGui::Begin("General Settings");

		ImGui::Text("Use W,A,S,D to move around.");
		ImGui::Text("Right Click for camera look.");
		ImGui::NewLine();

		// General
		ImGui::Text("General");
		if (ImGui::ColorEdit3("Clear Color", &m_ClearColor[0]))
		{
			glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0f);
		}

		if (m_Skybox)
		{
			if (ImGui::Checkbox("Skybox", &skyBox))
			{
				m_Skybox->SetEnabled(skyBox);
			}
		}

		if (ImGui::Checkbox("Draw Triangles", &drawLines))
		{
			auto flag = drawLines ? GL_LINE : GL_FILL;
			glPolygonMode(GL_FRONT_AND_BACK, flag);
		}

		// Camera Options
		ImGui::NewLine();
		ImGui::Text("Camera");
		if (ImGui::SliderFloat("Camera Speed", &cameraSpeed, 0.01f, 500.0f))
		{
			m_Camera->SetSpeed(cameraSpeed);
		}
		if (ImGui::SliderFloat("Camera FOV", &cameraFOV, 10.0f, 150.0f))
		{
			m_Camera->SetFOV(cameraFOV);
		}


		// Light Options
		ImGui::NewLine();
		ImGui::Text("Light");
		if (ImGui::ColorEdit3("Light Color", &lightColor[0]))
		{
			m_DirectionalLight->SetColor(lightColor);
		}

		if (ImGui::DragFloat3("Light Position", &lightPos[0]))
		{
			m_DirectionalLight->SetPosition(lightPos);
		}

		if (ImGui::SliderFloat("Ambient Light Strength", &m_AmbientLight, 0.0f, 1.0f))
		{
			auto shader = GetShader("modelShader");
			shader->Bind();
			shader->SetUniform1f("u_AmbientLight", m_AmbientLight);
		}

		if (ImGui::SliderFloat("Specular Strength", &m_SpecularStrength, 0.0f, 10.0f))
		{
			auto shader = GetShader("modelShader");
			shader->Bind();
			shader->SetUniform1f("u_SpecularStrength", m_SpecularStrength);
		}


		// Info text
		ImGui::NewLine();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void GLApplication::CalculateFrameTime()
	{
		static auto lastFrameTime = glfwGetTime();
		auto currentFrameTime = glfwGetTime();

		m_DeltaTime = static_cast<float>(currentFrameTime - lastFrameTime);
		lastFrameTime = currentFrameTime;
	}

	void GLApplication::OnCursorMove(double xpos, double ypos)
	{
		UpdateCameraRotation(xpos, ypos);
	}

	void GLApplication::UpdateCameraPosition()
	{
		if (glfwGetKey(m_Window, GLFW_KEY_A))
		{
			m_Camera->MoveX(1.0f * m_DeltaTime);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_D))
		{
			m_Camera->MoveX(-1.0f * m_DeltaTime);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_W))
		{
			m_Camera->MoveZ(1.0f * m_DeltaTime);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_S))
		{
			m_Camera->MoveZ(-1.0f * m_DeltaTime);
		}
	}


	void GLApplication::UpdateCameraRotation(double xpos, double ypos)
	{
		// imediate mode camera look
		static bool firstMouse = true;
		static double lastX = 0, lastY = 0;

		if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			auto xoffset = xpos - lastX;
			auto yoffset = lastY - ypos;

			lastX = xpos;
			lastY = ypos;

			m_Camera->Yaw(static_cast<float>(xoffset));
			m_Camera->Pitch(static_cast<float>(yoffset));
		}
		else if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstMouse = true;
		}
	}

	void GLApplication::InitDirectionalLight()
	{
		auto light = new Light(glm::vec3(0.0f), glm::vec3(1.0f));
		auto model = LoadModel("assets/models/shapes/sphere.fbx");

		if (model)
		{
			model->Scale(glm::vec3(0.005f));
			model->SetShader(GetShader("lampShader"));

			light->SetModel(model);
		}

		//light->SetColor(glm::vec3(1.0f, 0, 0));
		light->SetPosition(glm::vec3(1.0f, 20.0f, -70.0f));

		m_DirectionalLight = std::unique_ptr<Light>(light);
	}


	Model* GLApplication::LoadModel(const std::string& modelPath)
	{
		auto model = new Model();
		model->Load(modelPath);

		if (!model->IsLoaded())
		{
			delete model;
			return nullptr;
		}

		AddModel(model);
		return model;
	}

	void GLApplication::AddModel(Model* model)
	{
		m_Models.push_back(std::unique_ptr<Model>(model));
	}

	ShaderProgram* GLApplication::GetShader(const std::string& shaderName) const
	{
		auto it = m_Shaders.find(shaderName);
		if (it == m_Shaders.end())
		{
			return nullptr;
		}

		return it->second.get();
	}

	ShaderProgram* GLApplication::LoadShaders(const std::string& shaderName, const std::string& verShaderFile, const std::string& fragShaderFile)
	{
		auto shader = new ShaderProgram();
		shader->LoadShaders(verShaderFile, fragShaderFile);
		if (!shader->IsLinked())
		{
			assert(false);

			delete shader;
			return nullptr;
		}

		AddShader(shaderName, shader);
		return shader;
	}

	void GLApplication::AddShader(const std::string& shaderName, ShaderProgram* shader)
	{
		m_Shaders[shaderName] = std::unique_ptr<ShaderProgram>(shader);
	}

	void GLApplication::OnScroll(double xoffset, double yoffset)
	{

	}


	void GLApplication::OnKeyInput(int key, int scancode, int action, int mods)
	{

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

	void GlWindowResizeCallBack(GLFWwindow* window, int width, int height)
	{
		static auto glApp = static_cast<GLApplication*>(glfwGetWindowUserPointer(window));
		if (!glApp)
		{
			GLCORE_ERR("[GlCursorPosCallback] Window app pointer null.");
			return;
		}

		glViewport(0, 0, width, height);
	}

}
