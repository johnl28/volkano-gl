#pragma once
#include <vector>
#include <string>

#include "glad/glad.h"

namespace glcore {

	/**
	 * @brief Manages a cubemap texture for environment mapping in a 3D scene.
	 * @param texturesPaths A vector of strings containing the paths to the six textures for the cubemap.
	 */
	class CubeMap
	{
	public:
		CubeMap(std::vector<std::string> texturesPaths);
		~CubeMap();

		CubeMap(const CubeMap&) = delete;
		CubeMap& operator=(const CubeMap&) = delete;

		bool IsLoaded() { return m_Loaded; }
		void Bind();
		void UnBind();

	private:
		GLuint m_TextureID = 0;
		bool m_Loaded = false;
	};

}