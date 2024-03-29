#pragma once
#include "Core/ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Skybox.h"

namespace glcore {

	/**
	 * @brief Manages rendering operations in a 3D scene, including models and skyboxes.
	 */
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

	private:
		Renderer() {};

	};

}

