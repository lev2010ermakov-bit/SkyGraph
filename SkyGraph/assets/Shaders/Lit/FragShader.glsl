#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material{
    bool hasDiff;
    vec4 DiffuseColor;
    sampler2D DiffuseMap;

    bool hasSpec;
    float Specular;
    sampler2D SpecularMap;

    bool hasEmis;
    sampler2D EmissionMap;


    float Shiness;
    float minLight;
};

struct DirectionalLight{
    vec3 direction;
    vec3 color;
};

struct PointLight{
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{

};

uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform vec3 camPos;

out vec4 FragColor;

vec4 GetDirectional();

void main(){
    vec3 ambient_res;
    if (u_Material.hasDiff)
        ambient_res = vec3(u_Material.minLight) * texture(u_Material.DiffuseMap, TexCoords).xyz;
    else 
        ambient_res = vec3(u_Material.minLight) * u_Material.DiffuseColor.xyz;

    FragColor = GetDirectional() + vec4(ambient_res, 1);
}

vec4 GetDirectional(){
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-u_DirectionalLight.direction);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;
    vec3 ambient_res;

    if (u_Material.hasDiff){
        diffuse_res = diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        diffuse_res = diff * vec3(u_Material.DiffuseColor);
    }

    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = u_DirectionalLight.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = u_DirectionalLight.color * (spec * u_Material.Specular);

    vec3 emision_res;
    if (u_Material.hasEmis)
        emision_res = texture(u_Material.EmissionMap, TexCoords).xyz;

    return vec4(ambient_res + diffuse_res + specular_res + emision_res, 1.0f);
}