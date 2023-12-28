#include "Light.h"


namespace glcore {

	Light::Light()
	{
		m_Model = std::make_unique<Model>();
		m_Model->Load("assets/models/shapes/sphere.fbx");
	}

	void Light::Render(ShaderProgram* shader)
	{
		m_Model->Render(shader);
	}

}
