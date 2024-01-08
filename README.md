# volkano-gl

Volkano-gl is an interactive 3D simulation scene of a volcano eruption created with C++ and OpenGL.

The purpose of this project is to learn the best practices of modern OpenGL and have a better understanding of the computer graphics pipeline.


## Example
```cpp
#include "GLCore.h"

int main()
{
  auto app = new glcore::GLApplication(1280, 720, "MyApp");
  if (!app->IsContextInitialised())
  {
    return -1;
  }

  auto model = app->LoadModel("assets/models/shapes/square.fbx");
  if(model)
    model->Move(glm::vec3(0.0f, 0.0f, 20.0f));

  app->Run();

  return 0;
}
```

## Dependencies & Build

The project contains a Visual Studio 2022 solution with 2 projects associated:
- **OpenGL-Core** a static library that has the OpenGL implementation
- **Sandbox** an executable that implements the static library

All the external code should be located in a directory called **dependencies** placed at the same level as the solution. 

The dependencies structure should look like this
```
volkano-gl.sln

dependencies
  include/
    GLFW/
    stb/

  lib/
    glfw3.lib

  c/
    stb_image.cpp

```

Project Dependencies:
- [GLM](https://github.com/g-truc/glm)
- [GLFW](https://www.glfw.org/)
- [ASSIMP](https://github.com/assimp/assimp)
- [stb](https://github.com/nothings/stb)
- [Glad](https://glad.dav1d.de/)
- [ImGui](https://github.com/ocornut/imgui)

