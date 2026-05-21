#version 330 core

struct Material{
    vec3 color;

    bool hasTexture;
    sampler2D texture;
};

in vec2 TexCoords;

uniform Material u_Material;

out vec4 FragColor;

void main(){
    if (u_Material.hasTexture)
        FragColor = vec4(u_Material.color * texture(u_Material.texture, TexCoords).rgb, 1.0);
    else
        FragColor = vec4(u_Material.color.rgb, 1.0);
}