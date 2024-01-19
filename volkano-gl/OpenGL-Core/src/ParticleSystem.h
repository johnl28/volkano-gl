#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "Model.h"
#include "Camera.h"

#include "Core/ShaderProgram.h"

namespace glcore {

	struct Particle
	{
		glm::vec3 Position = glm::vec3(0);
		glm::vec3 Velocity = glm::vec3(1);
		glm::vec3 Rotation = glm::vec3(0);

		glm::vec4 ColorStart = glm::vec4(1);
		glm::vec4 ColorEnd = glm::vec4(1);

		float SizeStart = 1.0f;
		float SizeEnd = 5.0f;

		float LifeRemaining = 0.0f;
		float LifeTime = 1.0f;

		bool IsActive = false;
	};

	class ParticleSystem 
	{
	public:
		ParticleSystem(Model* model, ShaderProgram* shader);

		void OnRenderUI();
		void OnRender(Camera* camera);
		void OnUpdate(float deltaTime);
		void Emit(const Particle& particle);

		void SetParticleSettings(const Particle& particle) { m_ParticleSettings = particle; };
		const Particle& GetParticleSettings() const { return m_ParticleSettings; }

		void SetPosition(const glm::vec3 position) { m_Position = position; }

	private:
		Particle m_ParticleSettings;

		bool m_Physics = true;
		float m_Gravity = 1.0f;

		bool m_Enabled = false;
		int m_ParticleIndex = 999;
		
		int m_TotalActiveParticles = 0;
		float m_Radius = 85.0f;
		glm::vec3 m_Position = glm::vec3(0);

		std::unique_ptr<ShaderProgram> m_Shader = nullptr;
		std::unique_ptr<Model> m_Model = nullptr;
		std::vector<Particle> m_Particles;
	};

}


