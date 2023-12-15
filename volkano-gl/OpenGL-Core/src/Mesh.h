#pragma once
#include <memory>

#include "glm/glm.hpp"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

 
namespace glcore {

	class Mesh
	{
	public:
		Mesh();


	private:
		glm::vec3 m_rotation;


	private:
		std::unique_ptr<VertexArray> m_vertexArray;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<Texture> m_texture;
	};

}
