
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
	auto volcano = app.LoadModel("assets/models/volcano.fbx");
	volcano->Scale(glm::vec3(0.01f));
	volcano->Move(glm::vec3(0, 0, -50.0f));

	auto signaturePlane = app.LoadModel("assets/models/signature_plane.fbx");
	signaturePlane->Rotate(glm::vec3(0, 0, 0));
	signaturePlane->Move(glm::vec3(0, -50.0f, -50.0f));
	signaturePlane->Scale(glm::vec3(0.05f));

	// Load Texture for debugging purpose
	auto texture = glcore::Texture("assets/textures/GreyboxTextures/greybox_dark_solid.png");
	texture.Bind();

	auto particleShader = app.LoadShaders("particle", "assets/shaders/particle_vert.glsl", "assets/shaders/particle_frag.glsl");
	auto particleModel = app.LoadModel("assets/models/shapes/sphere.fbx", false);


	auto volcanoEffect = app.CreateParticleSystem(particleModel, particleShader);
	volcanoEffect->SetPosition(glm::vec3(-7.0f, 22.0f, -51.0f));

	glcore::Particle particle;
	particle.LifeTime = 3.0f;
	particle.ColorStart = { 1.0f, 0.0f, 0.0f, 1.0f };
	particle.ColorEnd = { 1.0f, 1.0f, 0.0f, 1.0f };

	particle.Velocity = { 1.0f, 1.5f, 1.0f };

	particle.SizeStart = 9.0f;
	particle.SizeEnd = 0.01f;

	volcanoEffect->SetParticleSettings(particle);


	app.Run();

	return EXIT_SUCCESS;
}

