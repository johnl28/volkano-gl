#pragma once
#include "GLFW/glfw3.h"

//#include "Camera.h"
//#include "Light.h"

namespace glcore {


	class UI
	{
	public:
		UI();

		void Destroy();
		void Initialise(GLFWwindow* window);
		void NewFrame();
		void Render();

		//void OnUI(Camera* camera, Light* light);
	};


}
