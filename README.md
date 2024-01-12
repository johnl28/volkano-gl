# volkano-gl

Volkano-gl is an interactive 3D simulation scene of a volcano eruption created with C++ and OpenGL as a University Project.

The purpose of this project is to demonstrate a basic understanding of modern OpenGL and the computer graphics pipeline.

Please keep in mind, that the choice to not use CMake/Premake or any other build system generator was for simplicity and the coursework requirements. 


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

The project contains a Visual Studio 2022 solution with the following projects associated:
- ``OpenGL-Core`` a static library that has the OpenGL implementation
- ``Sandbox`` an executable that implements the static library

All the external code should be located in a directory called ``dependencies`` placed in the ``OpenGL-Core`` project directory.


The dependencies structure should look like this
```
volkano-gl.sln

OpenGL-Core/dependencies
  include/
    assimp/
    glad/
    GLFW/
    glm/
    imgui/
    KHR/
    stb/

  lib/
    glfw3.lib
    assimp-vc143-mtd.lib

  c/
    stb_image.cpp
    glad.c

```

Project Dependencies:
- [GLM](https://github.com/g-truc/glm)
- [GLFW](https://www.glfw.org/)
- [ASSIMP](https://github.com/assimp/assimp)
- [stb](https://github.com/nothings/stb)
- [Glad](https://glad.dav1d.de/)
- [ImGui](https://github.com/ocornut/imgui)

