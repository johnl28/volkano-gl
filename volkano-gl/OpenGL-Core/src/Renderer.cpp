#include "Renderer.h"
#include "Mesh.h"
#include "Log.h"

namespace glcore {

	void Renderer::RenderModel(Model* model, Camera* camera, ShaderProgram* shader)
	{
		if (!model || !camera || !shader)
		{
			GLCORE_WARN("[Renderer] Cannot render model, Model: %d, Camera %d, Shader %d", model, camera, shader);
			return;
		}

		shader->Bind();
		shader->SetUniformMatrix4fv("u_View", camera->GetViewMatrix());
		shader->SetUniformMatrix4fv("u_Projection", camera->GetProjectionMatrix());

		for (auto& mesh : model->GetMeshes())
		{
			mesh->Bind();
			shader->SetUniformMatrix4fv("u_Transform", mesh->GetTransformMatrix());

			glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

}

