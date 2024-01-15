#version 460 core

out vec4 FragColor;

in vec3 FragTextureCoord;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, FragTextureCoord);
}
