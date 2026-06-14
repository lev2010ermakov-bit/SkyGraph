#include <Material.hpp>

namespace sky{
    Material::Material(){
        color = Color(255);
    }

    void Material::Bind(){

    }

    void Material::SetShader(Shader& s){
        shader = &s;
    }
}