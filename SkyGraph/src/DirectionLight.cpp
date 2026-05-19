#include <DirectionLight.hpp>
#include <string>

std::vector<DirectionLight*> DirectionLight::instances = std::vector<DirectionLight*>();

DirectionLight::DirectionLight(){
    instances.push_back(this);
}

void DirectionLight::BindToShader(Shader* s, int id){
    std::string direction_key = "u_DirLights[" + std::to_string(id) + "].direction";
    std::string color_key = "u_DirLights[" + std::to_string(id) + "].color";
    float col3[3] = {(float)color.r/255.f, (float)color.g/255.f, (float)color.b/255.f};

    s->SetVec3(direction_key.c_str(), front);
    s->SetVec3(color_key.c_str(), col3);
}

void DirectionLight::SetDirToShader(Shader* s){
    // need to write this function
    // takes closest light sources and give it to shader
}