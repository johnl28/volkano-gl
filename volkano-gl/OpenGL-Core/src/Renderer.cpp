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

