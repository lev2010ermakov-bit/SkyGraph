#version 330 core

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
    vec3 position;
    vec3 direction;

    vec3 color;

    float cutoff;
    float smothing_angle;

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;


#define DIRLIGHT_COUNT 6
#define POINTLIGHT_COUNT 6
#define SPOTLIGHT_COUNT 6

uniform Material u_Material;

uniform DirectionalLight u_DirLights[DIRLIGHT_COUNT];
uniform PointLight u_PointLights[POINTLIGHT_COUNT];
uniform SpotLight u_SpotLights[SPOTLIGHT_COUNT];

uniform vec3 camPos;

out vec4 FragColor;

vec4 GetDirectional(DirectionalLight Light, vec3 Normal, vec3 ViewDirection);
vec4 GetPoint(PointLight Light, vec3 Normal, vec3 ViewDirection);
vec4 GetSpot(SpotLight Light, vec3 Normal, vec3 ViewDirection);

void main(){
    vec3 ambient_res;
    vec3 emision_res;
    vec3 output;
    vec3 normal;
    vec3 view;

    normal = normalize(Normal);
    view = normalize(camPos - FragPos);
    if (u_Material.hasDiff)
        ambient_res = vec3(u_Material.minLight) * texture(u_Material.DiffuseMap, TexCoords).xyz;
    else 
        ambient_res = vec3(u_Material.minLight) * u_Material.DiffuseColor.xyz;

    if (u_Material.hasEmis)
        emision_res = texture(u_Material.EmissionMap, TexCoords).xyz;

    output += ambient_res;

    for (int i = 0; i < DIRLIGHT_COUNT; i++)
        GetDirectional(u_DirLights[i], normal, view);
    
    for (int i = 0; i < POINTLIGHT_COUNT; i++)
        GetPoint(u_PointLights[i], normal, view);

    for (int i = 0; i < SPOTLIGHT_COUNT; i++)
        GetSpot(u_SpotLights[i], normal, view);

    FragColor = vec4(output, 1.0);
}

vec4 GetDirectional(DirectionalLight Light, vec3 norm, vec3 ViewDirection){
    vec3 lightDir = normalize(-Light.direction);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

    if (u_Material.hasDiff){
        diffuse_res = diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        diffuse_res = diff * vec3(u_Material.DiffuseColor);
    }

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(ViewDirection, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = Light.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = Light.color * (spec * u_Material.Specular);

    return vec4(diffuse_res + specular_res, 1.0f);
}

vec4 GetPoint(PointLight Light, vec3 norm, vec3 ViewDirection){
    float distance = length(Light.position - FragPos);
    float attenuation = 1.0/(Light.constant + Light.linear * distance + Light.quadratic * pow(distance, 2));
    vec3 lightDir = normalize(Light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

    if (u_Material.hasDiff){
        diffuse_res = diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        diffuse_res = diff * vec3(u_Material.DiffuseColor);
    }

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(ViewDirection, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = Light.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = Light.color * (spec * u_Material.Specular);

    return vec4((diffuse_res + specular_res) * attenuation, 1.0);
}

vec4 GetSpot(SpotLight Light, vec3 norm, vec3 ViewDirection){
    float distance = length(Light.position - FragPos);
    float attenuation = 1.0/(Light.constant + Light.linear * distance + Light.quadratic * pow(distance, 2));
    vec3 lightDir = normalize(Light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

    if (u_Material.hasDiff){
        diffuse_res = diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        diffuse_res = diff * vec3(u_Material.DiffuseColor);
    }

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(ViewDirection, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = Light.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = Light.color * (spec * u_Material.Specular);
    float theta = dot(lightDir, normalize(-Light.direction));
    float epsilon = Light.smothing_angle - Light.cutoff;
    float intensity = clamp((theta - Light.smothing_angle)/epsilon, 0.0, 1.0); 
    if (theta > Light.cutoff)
        return vec4((diffuse_res + specular_res) * attenuation * intensity, 1.0);
    else 
        return vec4(0.0);
}