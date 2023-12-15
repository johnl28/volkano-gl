#version 400 core

layout (location = 0) in vec3 verPos;
layout (location = 1) in vec2 verTextureCoord;

out vec2 FragTextureCoord;

void main()
{
	gl_Position = vec4(verPos.x, verPos.y, verPos.z, 1.0f);
	FragTextureCoord = verTextureCoord;
}