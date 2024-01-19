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
		shader->SetUniformVec3("u_ViewPos", camera->GetPosition());
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

		if (!skybox->IsEnabled())
		{
			return;
		}

		glDepthFunc(GL_LEQUAL);

		glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix()));


		auto shader = skybox->GetShader();
		shader->Bind();
		shader->SetUniformVec4("u_AmbientColor", skybox->GetAmbientColor());
		shader->SetUniformMatrix4fv("u_Projection", camera->GetProjectionMatrix());
		shader->SetUniformMatrix4fv("u_View", view);

		skybox->GetCubemap()->Bind();
		auto model = skybox->GetModel();
		for (auto& mesh : model->GetMeshes())
		{
			mesh->Bind();

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}

		glDepthFunc(GL_LESS);
	}


}

