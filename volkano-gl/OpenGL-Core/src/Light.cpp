#include "Light.h"


namespace glcore {

	Light::Light(const glm::vec3& position, const glm::vec3& color):
		m_Position(position), m_Color(color)
	{

	}

	void Light::SetModel(Model* model)
	{
		m_Model = model;
		UpdateModel();
	}

	void Light::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		UpdateModel();
	}

	void Light::UpdateModel()
	{
		if (!m_Model)
		{
			return;
		}

		m_Model->SetPosition(m_Position);
	}

}
