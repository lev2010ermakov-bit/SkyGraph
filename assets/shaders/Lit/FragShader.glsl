#version 330 core

struct Material{
    vec3 ShadowColor;

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
    float smoothing_angle;

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;


#define DIRLIGHT_COUNT 2
#define POINTLIGHT_COUNT 1
#define SPOTLIGHT_COUNT 2

uniform Material u_Material;

uniform DirectionalLight u_DirLights[DIRLIGHT_COUNT];
uniform PointLight u_PointLights[POINTLIGHT_COUNT];
uniform SpotLight u_SpotLights[SPOTLIGHT_COUNT];

uniform vec3 camPos;

out vec4 FragColor;

vec3 GetDirectional(DirectionalLight Light, vec3 Normal, vec3 ViewDirection);
vec3 GetPoint(PointLight Light, vec3 Normal, vec3 ViewDirection);
vec3 GetSpot(SpotLight Light, vec3 Normal, vec3 ViewDirection);

void main(){
    vec3 ambient_res;
    vec3 emision_res;
    vec3 output;
    vec3 normal;
    vec3 view;

    normal = normalize(Normal);
    view = normalize(camPos - FragPos);
    if (u_Material.hasDiff)
        ambient_res = u_Material.ShadowColor * texture(u_Material.DiffuseMap, TexCoords).xyz;
    else 
        ambient_res = u_Material.ShadowColor * u_Material.DiffuseColor.xyz;

    if (u_Material.hasEmis)
        emision_res = texture(u_Material.EmissionMap, TexCoords).xyz;

    for (int i = 0; i < DIRLIGHT_COUNT; i++)
        output += GetDirectional(u_DirLights[i], normal, view);
    
    for (int i = 0; i < POINTLIGHT_COUNT; i++)
        output += GetPoint(u_PointLights[i], normal, view);

    for (int i = 0; i < SPOTLIGHT_COUNT; i++)
        output += GetSpot(u_SpotLights[i], normal, view);

    output += ambient_res;

    FragColor = vec4(output, 1.0);
}

vec3 GetDirectional(DirectionalLight Light, vec3 norm, vec3 ViewDirection){
    vec3 lightDir = normalize(-Light.direction);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

    if (u_Material.hasDiff){
        diffuse_res = Light.color * diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        diffuse_res = Light.color * diff * vec3(u_Material.DiffuseColor);
    }

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(ViewDirection, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = Light.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz * u_Material.Specular);
    else 
        specular_res = Light.color * (spec * u_Material.Specular);

    return diffuse_res + specular_res;
}

vec3 GetPoint(PointLight Light, vec3 norm, vec3 ViewDirection){
    float distance = length(Light.position - FragPos);
    float attenuation = 1.0/(Light.constant + Light.linear * distance + Light.quadratic * pow(distance, 2));
    vec3 lightDir = normalize(Light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

    if (u_Material.hasDiff){
        diffuse_res = Light.color * diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        diffuse_res = Light.color * diff * vec3(u_Material.DiffuseColor);
    }

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(ViewDirection, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = Light.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = Light.color * (spec * u_Material.Specular);

    return (diffuse_res + specular_res) * attenuation;
}

vec3 GetSpot(SpotLight Light, vec3 norm, vec3 ViewDirection){
    float distance = length(Light.position - FragPos);
    float attenuation = 1.0/(Light.constant + Light.linear * distance + Light.quadratic * (distance * distance));
    vec3 lightDir = normalize(Light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

    if (u_Material.hasDiff){
        diffuse_res = Light.color * diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        diffuse_res = Light.color * diff * vec3(u_Material.DiffuseColor);
    }

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(ViewDirection, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = Light.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = Light.color * (spec * u_Material.Specular);
    float theta = dot(lightDir, normalize(-Light.direction));
    float epsilon = Light.smoothing_angle - Light.cutoff;
    float intensity = clamp((theta - Light.smoothing_angle)/epsilon, 0.0, 1.0); 
    if (theta > Light.cutoff)
        return (diffuse_res + specular_res) * attenuation * intensity;
    else 
        return vec3(0.0);
}