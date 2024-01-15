#version 460 core

in vec2 FragTextureCoord;
in vec3 FragNormals;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D u_Texture;

uniform float u_AmbientLight;
uniform float u_SpecularStrength;

uniform vec3 u_LightPositon;       
uniform vec3 u_LightColor;
uniform vec3 u_ViewPos;


vec3 CalculateAmbientLight();
vec3 CalculateDiffuseLight(vec3 normal, vec3 lightDir);
vec3 CalculateSpecularLight(vec3 normal, vec3 lightDir, vec3 viewDir);

void main()
{
	vec3 textureColor = texture(u_Texture, FragTextureCoord).rgb;

    vec3 lightDir = normalize(u_LightPositon - FragPos);
	vec3 norm = normalize(FragNormals);
    vec3 viewDir = normalize(u_ViewPos - FragPos);


    vec3 ambient = CalculateAmbientLight();
    vec3 diffuse = CalculateDiffuseLight(norm, lightDir);
    vec3 specular = CalculateSpecularLight(norm, lightDir, viewDir);

    vec3 result = (ambient + diffuse + specular) * textureColor;

	FragColor = vec4(result, 1.0);
}


vec3 CalculateAmbientLight()
{
    // todo: make ambientStrength a uniform
    //float ambientStrength = 0.5;

    return u_AmbientLight * u_LightColor;
}

vec3 CalculateDiffuseLight(vec3 normal, vec3 lightDir)
{
    float diff = max(dot(normal, lightDir), 0.0);
    
    return diff * u_LightColor;
}

vec3 CalculateSpecularLight(vec3 normal, vec3 lightDir, vec3 viewDir)
{
    // todo: use uniform
    //float specularStrength = 0.8;

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return u_SpecularStrength * spec * u_LightColor;
}