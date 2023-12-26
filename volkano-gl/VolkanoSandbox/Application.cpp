
#include <cstdlib>

#include "GLCore.h"

#include <memory>

int main()
{
	glcore::GLApplication app(1280, 720, "Hello OpenGL");

	if (!app.IsContextInitialised())
	{
		return EXIT_FAILURE;
	}

	//auto plane = app.LoadModel("assets/models/shapes/cube.fbx");
	//plane->Scale(glm::vec3(20.0f, 20.0f, 1.0f));

	//plane->Rotate(glm::vec3(0.0f, 0.0f, 90.0f));

	app.Run();

	return EXIT_SUCCESS;
}

