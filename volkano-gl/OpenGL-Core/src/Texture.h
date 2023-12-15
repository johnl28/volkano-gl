#pragma once
#include <string>

#include "glad/glad.h"
#include "stb/stb_image.h"


class Texture
{
public:
	Texture(const std::string& texturePath);
	~Texture();

	void Bind(GLuint sampler = 0) const;
	void UnBind() const;

private:
	GLuint m_textureID = 0;

	int m_width = 0;
	int m_height = 0;
	int m_BPP = 0;
};
