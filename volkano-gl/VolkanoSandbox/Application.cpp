
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


	// Load Volcano Model
	auto volcano = app.LoadModel("assets/models/volcanofull.fbx");
	volcano->Scale(glm::vec3(0.1f));
	volcano->Move(glm::vec3(0, 0, -50.0f));
	//auto volcanoTexture = new glcore::Texture("assets/textures/volcano_texture.jpg");
	//auto mesh = volcano->GetMesh(0);
	//mesh->SetTexture(volcanoTexture);

	// Load Texture for debugging purpose
	auto texture = glcore::Texture("assets/textures/GreyboxTextures/greybox_grey_grid.png");
	texture.Bind();

	auto particleShader = app.LoadShaders("particle", "assets/shaders/particle_vert.glsl", "assets/shaders/particle_frag.glsl");
	auto particleModel = app.LoadModel("assets/models/shapes/sphere.fbx", false);


	auto volcanoEffect = app.CreateParticleSystem(particleModel, particleShader);
	glcore::Particle particle;
	particle.LifeTime = 2.0f;
	particle.ColorStart = { 1.0f, 0.0f, 0.0f, 1.0f };
	particle.ColorEnd = { 1.0f, 1.0f, 0.0f, 1.0f };

	particle.Velocity = { 1.0f, 0.3f, 1.0f };

	particle.SizeEnd = 5.0f;

	volcanoEffect->SetPosition(glm::vec3(0, 5.0f, -50.0f));
	volcanoEffect->SetParticleSettings(particle);


	app.Run();

	return EXIT_SUCCESS;
}

