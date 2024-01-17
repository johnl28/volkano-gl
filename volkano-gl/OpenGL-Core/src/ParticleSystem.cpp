
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "glad/glad.h"

#include "Log.h"
#include "ParticleSystem.h"
#include "GlRandom.h"

namespace glcore {

	ParticleSystem::ParticleSystem(Model* model, ShaderProgram* shader)
	{
		m_Model = std::unique_ptr<Model>(model);
		m_Shader = std::unique_ptr<ShaderProgram>(shader);


		m_Particles.resize(1000);
	}

	void ParticleSystem::Emit(const Particle& newParticle)
	{
		Particle& particle = m_Particles[m_ParticleIndex];

		memcpy(&particle, &newParticle, sizeof(Particle));

		particle.LifeRemaining = particle.LifeTime;
		particle.Position = m_Position;
		particle.IsActive = true;

		float r = m_Radius / 180.0f;

		particle.Velocity *= glm::vec3(Random::Float(-r, r), 1.0f, Random::Float(-r, r));

		if (--m_ParticleIndex < 0)
		{
			m_ParticleIndex = m_Particles.size() - 1;
		}
	}

	void ParticleSystem::OnUpdate(float deltaTime)
	{
		if (m_Enabled)
		{
			Emit(m_ParticleSettings);
		}

		m_TotalActiveParticles = 0;

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

			if (m_Physics)
			{
				particle.Velocity.y += -m_Gravity * deltaTime;
			}

			particle.Position += particle.Velocity;

			particle.Rotation.x += 2.0f * deltaTime;

			++m_TotalActiveParticles;
		}
	}

	void ParticleSystem::OnRenderUI()
	{
		ImGui::Begin("Volcano Settings");

		ImGui::Checkbox("Enabled", &m_Enabled);
		ImGui::Checkbox("Physics Simulation", &m_Physics);
		if (m_Physics)
		{
			ImGui::SliderFloat("Gravity Force", &m_Gravity, 0.01f, 2.0f);
		}

		ImGui::SliderFloat("Life Time", &m_ParticleSettings.LifeTime, 0.1f, 10.0f);
		ImGui::SliderFloat("Radius", &m_Radius, 1.0f, 180.0f);


		ImGui::SliderFloat("Velocity", &m_ParticleSettings.Velocity.y, 0.1f, 10.0f);
		ImGui::ColorEdit4("Start Color", &m_ParticleSettings.ColorStart[0]);
		ImGui::ColorEdit4("End Color", &m_ParticleSettings.ColorEnd[0]);

		ImGui::SliderFloat("Start Size", &m_ParticleSettings.SizeStart, 0.1f, 10.0f);
		ImGui::SliderFloat("End Size", &m_ParticleSettings.SizeEnd, 0.1f, 10.0f);

		ImGui::Text("Total Particles %d", m_TotalActiveParticles);

		ImGui::End();
	}

	void ParticleSystem::OnRender(Camera* camera)
	{
		auto mesh = m_Model->GetMesh(0);
		if (!mesh)
		{
			GLCORE_WARN("[Particle System] Null mesh.");
			return;
		}

		mesh->Bind();
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4fv("u_View", camera->GetViewMatrix());
		m_Shader->SetUniformMatrix4fv("u_Projection", camera->GetProjectionMatrix());

		glm::mat4 transformation(1.0f);
		transformation = glm::translate(transformation, m_Position);
		transformation = glm::scale(transformation, glm::vec3(0.01f));

		m_Shader->SetUniformMatrix4fv("u_Transform", transformation);


		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

		for (auto& particle : m_Particles)
		{
			if(!particle.IsActive)
			{
				continue;
			}

			mesh->Bind();

			float lifePercentage = particle.LifeRemaining / particle.LifeTime;

			float scale = glm::lerp(particle.SizeEnd, particle.SizeStart, lifePercentage);
			auto color = glm::lerp(particle.ColorEnd, particle.ColorStart, lifePercentage);

			//color.a = lifePercentage;


			glm::mat4 transformation(1.0f);
			transformation = glm::translate(transformation, particle.Position);
			transformation = glm::scale(transformation, glm::vec3(0.01f) * scale);
			transformation = glm::rotate(transformation, particle.Rotation.x, glm::vec3(1.0f, 0, 0));

			m_Shader->SetUniformVec4("u_Color", color);
			m_Shader->SetUniformMatrix4fv("u_Transform", transformation);

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}

	}

}


