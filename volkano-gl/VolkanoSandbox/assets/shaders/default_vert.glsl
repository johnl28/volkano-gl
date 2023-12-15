#version 400 core

layout (location = 0) in vec3 verPos;
layout (location = 1) in vec2 verTextureCoord;

out vec2 FragTextureCoord;

uniform mat4 u_Transform;

void main()
{
	gl_Position = u_Transform * vec4(verPos, 1.0f);
	FragTextureCoord = verTextureCoord;
}