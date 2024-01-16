#include "ParticleSystem.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"

namespace glcore {

	ParticleSystem::ParticleSystem(Model* model)
	{
		m_Model = std::unique_ptr<Model>(model);
		m_Shader = std::make_unique<ShaderProgram>();
		m_Shader->LoadShaders("assets/shaders/particle_vert.glsl", "assets/shaders/particle_frag.glsl");

		m_Particles.resize(1000);
	}

	void ParticleSystem::OnUpdate(float deltaTime)
	{
		for (auto& particle : m_Particles)
		{
			if (!particle.IsActive)
			{
				continue;
			}
			if (particle.LifeRemaining < 0.0f)
			{
				particle.IsActive = false;
				continue;
			}

			particle.LifeRemaining -= deltaTime;
			particle.Position += particle.Velocity;
			particle.Rotation *= 0.01f * deltaTime;

		}
	}

	void ParticleSystem::Emit(const Particle& newParticle)
	{
		Particle& particle = m_Particles[m_ParticleIndex];

		memcpy(&particle, &newParticle, sizeof(Particle));



		if (--m_ParticleIndex < 0)
		{
			m_ParticleIndex = m_Particles.size() - 1;
		}
	}

	void ParticleSystem::OnRender(Camera* camera)
	{
		auto mesh = m_Model->GetMesh(0);
		if (!mesh)
		{
			return;
		}

		mesh->Bind();

		for (auto& particle : m_Particles)
		{
			if(!particle.IsActive)
			{
				continue;
			}

			mesh->Bind();

			glm::mat4 transformation(1.0f);
			transformation = glm::translate(transformation, m_Position);
			m_Shader->Bind();
			m_Shader->SetUniformMatrix4fv("u_Transform", transformation);

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}

	}

}


