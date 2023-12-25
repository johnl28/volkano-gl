#include "Texture.h"
#include "Log.h"


namespace glcore {

	Texture::Texture(const std::string& texturePath, bool flip)
	{
		if (flip)
		{
			stbi_set_flip_vertically_on_load(1);
		}

		auto textureBuffer = stbi_load(texturePath.c_str(), &m_width, &m_height, &m_BPP, 4);
		if (!textureBuffer)
		{
			GLCORE_ERR("[Texture] Failed to load texture file %s", texturePath.c_str());
			return;
		}

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
		stbi_image_free(textureBuffer);

		UnBind();
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureID);
	}

	void Texture::Bind(GLuint sampler) const
	{
		glBindSampler(GL_TEXTURE_2D, GL_TEXTURE0 + sampler);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


}