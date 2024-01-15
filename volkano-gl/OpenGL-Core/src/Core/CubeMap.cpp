
#include "stb/stb_image.h"


#include "Log.h"
#include "CubeMap.h"




namespace glcore {

	CubeMap::CubeMap(std::vector<std::string> texturesPaths)
	{
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < texturesPaths.size(); i++)
        {
            auto &texturePath = texturesPaths[i];

            unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );

                stbi_image_free(data);
            }
            else
            {
                GLCORE_ERR("[CubeMap] Failed to load texture: %s", texturePath.c_str());
                stbi_image_free(data);
                return;
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        m_Loaded = true;
	}

    CubeMap::~CubeMap()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void CubeMap::Bind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
    }

    void CubeMap::UnBind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}