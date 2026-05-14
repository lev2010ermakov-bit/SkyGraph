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
    vec3 position;
    vec3 direction;

    vec3 color;

    float cutoff;
    float smothing_angle;

    float constant;
    float linear;
    float quadratic;
};

uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;
uniform vec3 camPos;

out vec4 FragColor;

vec4 GetDirectional();
vec4 GetPoint();
vec4 GetSpot();

void main(){
    vec3 ambient_res;
    if (u_Material.hasDiff)
        ambient_res = vec3(u_Material.minLight) * texture(u_Material.DiffuseMap, TexCoords).xyz;
    else 
        ambient_res = vec3(u_Material.minLight) * u_Material.DiffuseColor.xyz;

    vec3 emision_res;
    if (u_Material.hasEmis)
        emision_res = texture(u_Material.EmissionMap, TexCoords).xyz;

    FragColor = GetDirectional() + GetPoint() + GetSpot() + vec4(ambient_res + emision_res, 1);
}

vec4 GetDirectional(){
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-u_DirectionalLight.direction);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

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

    return vec4(diffuse_res + specular_res, 1.0f);
}

vec4 GetPoint(){
    float distance = length(u_PointLight.position - FragPos);
    float attenuation = 1.0/(u_PointLight.constant + u_PointLight.linear * distance + u_PointLight.quadratic * pow(distance, 2));
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_PointLight.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

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
        specular_res = u_PointLight.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = u_PointLight.color * (spec * u_Material.Specular);

    return vec4((diffuse_res + specular_res) * attenuation, 1.0);
}

vec4 GetSpot(){
    float distance = length(u_SpotLight.position - FragPos);
    float attenuation = 1.0/(u_SpotLight.constant + u_SpotLight.linear * distance + u_SpotLight.quadratic * pow(distance, 2));
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_SpotLight.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;

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
        specular_res = u_SpotLight.color * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = u_SpotLight.color * (spec * u_Material.Specular);
    float theta = dot(lightDir, normalize(-u_SpotLight.direction));
    float epsilon = u_SpotLight.smothing_angle - u_SpotLight.cutoff;
    float intensity = clamp((theta - u_SpotLight.smothing_angle)/epsilon, 0.0, 1.0); 
    if (theta > u_SpotLight.cutoff)
        return vec4((diffuse_res + specular_res) * attenuation * intensity, 1.0);
    else 
        return vec4(0.0);
}