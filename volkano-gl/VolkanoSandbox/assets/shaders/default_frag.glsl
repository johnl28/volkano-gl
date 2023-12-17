#version 400 core

in vec2 FragTextureCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, FragTextureCoord) + vec4(0.0f, 0.0f, 0.0f, 1.0f);
}


