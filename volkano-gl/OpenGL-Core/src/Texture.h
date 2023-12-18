#pragma once
#include <string>

#include "glad/glad.h"
#include "stb/stb_image.h"

namespace glcore {

	class Texture
	{
	public:
		Texture(const std::string& texturePath, bool flip = false);
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void Bind(GLuint sampler = 0) const;
		void UnBind() const;

	private:
		GLuint m_textureID = 0;

		int m_width = 0;
		int m_height = 0;
		int m_BPP = 0;
	};

}