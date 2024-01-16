#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "Model.h"
#include "Camera.h"

#include "Core/ShaderProgram.h"

namespace glcore {

	struct Particle
	{
		glm::vec3 Position;
		glm::vec3 Velocity;
		glm::vec3 Rotation;

		glm::vec3 Color = glm::vec3(1);

		float LifeRemaining = 0.0f;
		float LifeTime = 1.0f;

		bool IsActive = false;
	};

	class ParticleSystem 
	{
	public:
		ParticleSystem(Model* model);

		void OnRender(Camera* camera);
		void OnUpdate(float deltaTime);
		void Emit(const Particle& particle);

	private:
		int m_ParticleIndex = 999;

		std::unique_ptr<ShaderProgram> m_Shader = nullptr;
		std::unique_ptr<Model> m_Model = nullptr;
		glm::vec3 m_Position = glm::vec3(0);
		std::vector<Particle> m_Particles;
	};

}


