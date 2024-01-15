#include "Renderer.h"
#include "Mesh.h"
#include "Log.h"

namespace glcore {

	void Renderer::RenderModel(Model* model, Camera* camera, ShaderProgram* shader, Light* light)
	{
		if (!model || !camera || !shader)
		{
			GLCORE_WARN("[Renderer] Cannot render model, Model: %d, Camera %d, Shader %d", model, camera, shader);
			return;
		}

		shader->Bind();
		shader->SetUniformMatrix4fv("u_View", camera->GetViewMatrix());
		shader->SetUniformMatrix4fv("u_Projection", camera->GetProjectionMatrix());
		shader->SetUniformVec3("u_LightPositon", light->GetPosition());
		shader->SetUniformVec3("u_LightColor", light->GetColor());


		for (auto& mesh : model->GetMeshes())
		{
			mesh->Bind();
			shader->SetUniformMatrix4fv("u_Transform", mesh->GetTransformMatrix());

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

	void Renderer::RenderSkybox(Skybox* skybox, Camera* camera)
	{
		if (!skybox)
		{
			GLCORE_WARN("[Renderer] Cannot render skybox, Skybox: %d", skybox);
			return;
		}

		glDepthFunc(GL_LEQUAL);
		//glDepthMask(GL_FALSE);

		glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix()));


		auto shader = skybox->GetShader();
		shader->Bind();
		shader->SetUniformMatrix4fv("u_Projection", camera->GetProjectionMatrix());
		shader->SetUniformMatrix4fv("u_View", view);
		//shader->SetUniform1i("skybox", 0);

		skybox->GetCubemap()->Bind();
		auto model = skybox->GetModel();
		for (auto& mesh : model->GetMeshes())
		{
			mesh->Bind();

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}

		glDepthFunc(GL_LESS);
		//glDepthMask(GL_TRUE);
	}

	void Renderer::RenderLight(Light* light, Camera* camera, ShaderProgram* shader)
	{
		if (!light || !camera || !shader)
		{
			GLCORE_WARN("[Renderer] Cannot render model, Light: %d, Camera %d, Shader %d", light, camera, shader);
			return;
		}

		auto model = light->GetModel();
		if (!model)
		{
			return;
		}

		shader->Bind();
		shader->SetUniformMatrix4fv("u_View", camera->GetViewMatrix());
		shader->SetUniformMatrix4fv("u_Projection", camera->GetProjectionMatrix());
		shader->SetUniformVec3("u_LightColor", light->GetColor());

		for (auto& mesh : model->GetMeshes())
		{
			mesh->Bind();
			shader->SetUniformMatrix4fv("u_Transform", mesh->GetTransformMatrix());

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

}

