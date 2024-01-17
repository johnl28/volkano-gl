#version 460 core

out vec4 FragColor;

in vec3 FragTextureCoord;

uniform samplerCube skybox;
uniform vec4 u_AmbientColor;

void main()
{    
    FragColor = u_AmbientColor * texture(skybox, FragTextureCoord);
}
