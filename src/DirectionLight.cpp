#include <DirectionLight.hpp>
#include <string>

namespace sky{
    DirectionLight::DirectionLight(){
        color = Color(255);
    }

    void DirectionLight::BindToShader(Shader& shader, int id){
        std::string direction_key = "u_DirLights[" + std::to_string(id) + "].direction";
        std::string color_key = "u_DirLights[" + std::to_string(id) + "].color";

        shader.SetVec3(direction_key.c_str(), getLocals().front);
        shader.SetVec3(color_key.c_str(), color.glCol3());
    }
}