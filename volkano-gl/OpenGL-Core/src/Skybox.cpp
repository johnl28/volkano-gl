#include "Skybox.h"


namespace glcore {

	Skybox::Skybox(Model* model, CubeMap* cubemap, ShaderProgram* shader):
		m_Model(model), m_Cubemap(cubemap), m_Shader(shader)
	{
	}

}
