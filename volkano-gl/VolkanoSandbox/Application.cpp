
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

	auto volcano = app.LoadModel("assets/models/volcanofull.fbx");
	volcano->Scale(glm::vec3(0.1f));
	volcano->Move(glm::vec3(0, 0, -50.0f));


	app.Run();

	return EXIT_SUCCESS;
}

