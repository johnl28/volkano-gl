#pragma once
#include <string>

#include "glad/glad.h"
#include "stb/stb_image.h"

namespace glcore {


	/**
	 * @brief Manages an OpenGL texture, handling loading from file, binding, and unbinding.
	 * @param texturePath Path to the texture file.
	 * @param flip Optional parameter to flip the texture vertically during loading (default is false).
	 */
	class Texture
	{
	public:
		Texture(const std::string& texturePath, bool flip = false);
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void Bind(GLuint sampler = 0) const;
		void UnBind() const;

		bool IsLoaded() const { return m_Loaded; }

	private:
		GLuint m_textureID = 0;
		bool m_Loaded = false;

		int m_Width = 0;
		int m_Height = 0;
		int m_Channels = 0;
	};

}