#version 460 core

in vec2 FragTextureCoord;
in vec3 FragNormals;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D u_Texture;

uniform vec3 u_LightPositon;       
uniform vec3 u_LightColor;
uniform vec3 u_ViewPos;

void main()
{
    vec3 u_LightColor = vec3(1.0);
	vec3 textureColor = texture(u_Texture, FragTextureCoord).rgb;

    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;

    // Diffuse
    vec3 lightDir = normalize(u_LightPositon - FragPos);

	vec3 norm = normalize(FragNormals);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuse = diff * u_LightColor;
    

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;


    vec3 result = (ambient + diffuse + specular) * textureColor;


	FragColor = vec4(result, 1.0);
}


