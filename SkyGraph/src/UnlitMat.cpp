#include <UnlitMat.hpp>

UnlitMat::UnlitMat(){
    
}

UnlitMat::UnlitMat(Shader& s){
    shader = &s;
    shader->SetInt("u_Material.texture", 0);
}

void UnlitMat::Bind(){
    if (!shader) return;

    shader->SetColor("u_Material.color", color);
    shader->SetBool("u_Material.hasTextxure", texture != nullptr);
    if (texture){
        glActiveTexture(GL_TEXTURE0);
        texture->Bind();
    }
    shader->use();
}