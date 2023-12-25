
#include <cstdlib>

#include "GLCore.h"

#include <memory>

int main()
{
	glcore::GLApplication app(1000, 700, "Hello OpenGL");

	if (!app.IsContextInitialised())
	{
		return EXIT_FAILURE;
	}

	glcore::Vertex vertices[] = {

		// front face
		{
			glm::vec3 { -0.5f, -0.5f, 0.5f },
			glm::vec2 { 0.0f, 1.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }
		},

		{
			glm::vec3 { 0.5f, -0.5f, 0.5f },
			glm::vec2 { 1.0f, 1.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }
		},

		{
			glm::vec3 { -0.5f, 0.5f, 0.5f },
			glm::vec2 { 0.0f, 0.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }
		},

		{
			glm::vec3 { 0.5f, 0.5f, 0.5f },
			glm::vec2 { 1.0f, 0.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }
		},


		// back face
		{
			glm::vec3 { -0.5f, -0.5f, -0.5f },
			glm::vec2 { 1.0f, 1.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }
		},

		{
			glm::vec3 { 0.5f, -0.5f, -0.5f },
			glm::vec2 { 0.0f, 1.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }

		},

		{
			glm::vec3 { -0.5f, 0.5f, -0.5f },
			glm::vec2 { 1.0f, 0.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }
		},

		{
			glm::vec3 { 0.5f, 0.5f, -0.5f },
			glm::vec2 { 0.0f, 0.0f },
			glm::vec3 { 0.0f, 0.0f, 0.0f }
		},
	};



	GLuint indicies[] = {
		// front
		0, 1, 2,
		1, 3, 2,

		// back
		4, 5, 6,
		5, 7, 6,

		// left
		4, 0, 6,
		0, 2, 6,

		// right
		5, 1, 7,
		7, 3, 1,

	};

	auto mesh = new glcore::Mesh(vertices, sizeof(vertices), indicies, sizeof(indicies) / sizeof(GLuint));
	//mesh->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	mesh->Rotate(glm::vec3(20.0f, 20.0f, 0.0f));
	//app.AddMesh(mesh);



	app.Run();

	return EXIT_SUCCESS;
}

