#include <DirectionLight.hpp>
#include <algorithm>
#include <string>
#include <iostream>

std::vector<DirectionLight*> DirectionLight::instances = std::vector<DirectionLight*>();
int DirectionLight::LightsMatchingCount = 2;

DirectionLight::DirectionLight(){
    instances.push_back(this);
    if (instances.capacity() > LightsMatchingCount){
        std::cout << "\033[93mWarning: count of Directional light source is bigger then count of matching ones! this Light Source will not be matched!\033[0m" << std::endl;
    }
}

void DirectionLight::BindToShader(Shader& shader, int id){
    std::string direction_key = "u_DirLights[" + std::to_string(id) + "].direction";
    std::string color_key = "u_DirLights[" + std::to_string(id) + "].color";

    UpdateLocalVectors();
    shader.SetVec3(direction_key.c_str(), front);
    shader.SetVec3(color_key.c_str(), color.glCol3());
}

void DirectionLight::ShaderSet(Shader& shader){
    for (int i = 0; i < LightsMatchingCount - std::clamp(LightsMatchingCount-(int)instances.capacity(), 0, LightsMatchingCount); i++){
        instances[i]->BindToShader(shader, i);
    }
}

void DirectionLight::destroy(){
    instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());
}