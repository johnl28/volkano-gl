#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoord;
layout (location = 2) in vec3 aNormals;


uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_Projection * u_View * u_Transform * vec4(aPos, 1.0);
}

