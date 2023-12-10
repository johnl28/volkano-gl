
#include <cstdlib>

#include "GLCore.h"

int main()
{
	glcore::GLApplication app(500, 500, "Hello OpenGL");

	if (!app.IsInitialised())
	{
		return EXIT_FAILURE;
	}

	app.Run();

	return EXIT_SUCCESS;
}

