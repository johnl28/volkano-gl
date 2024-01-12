#pragma once
#include "Core/ShaderProgram.h"
#include "Camera.h"
#include "Model.h"

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

		void RenderModel(Model* model, Camera* camera, ShaderProgram* shader);

	private:
		Renderer();

	};

}

