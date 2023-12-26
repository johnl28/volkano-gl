#version 460 core

in vec2 FragTextureCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;

uniform vec3 u_LightColor;

void main()
{
    vec3 u_LightColor = vec3(1.0);
	FragColor = vec4(u_LightColor, 1.0f);
}


