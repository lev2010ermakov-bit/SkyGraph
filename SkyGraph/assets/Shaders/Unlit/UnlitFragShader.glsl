#version 330 core

struct Material{
    vec4 color;

    bool hasTexture;
    sampler2D texture;
};

in vec2 TexCoords;

uniform Material u_Material;

out vec4 FragColor;

void main(){
    if (u_Material.hasTexture)
        FragColor = u_Material.color * texture(u_Material.texture, TexCoords);
    else
        FragColor = u_Material.color;
}