#version 460 core

out vec4 FragColor;

uniform vec3 u_LightColor;

void main()
{
	FragColor = vec4(u_LightColor, 1.0f);
}


