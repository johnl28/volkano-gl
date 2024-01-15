#pragma once
#include "Core/ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Skybox.h"

namespace glcore {

	class Renderer
	{
	public:

		// Remove copy constructor and assignment operator
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		static Renderer& Get()
		{
			static Renderer instance;
			return instance;
		}

		void RenderModel(Model* model, Camera* camera, ShaderProgram* shader, Light* light);
		void RenderSkybox(Skybox* skybox, Camera* camera);
		void RenderLight(Light* light, Camera* camera, ShaderProgram* shader);

	private:
		Renderer() {};

	};

}

