
#include <cstdlib>

#include "GLCore.h"

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

}

int main()
{
	glcore::GLApplication app(1000, 700, "Hello OpenGL");

	if (!app.IsInitialised())
	{
		return EXIT_FAILURE;
	}


	app.SetSrollCallback(ScrollCallback);
	app.Run();

	return EXIT_SUCCESS;
}

