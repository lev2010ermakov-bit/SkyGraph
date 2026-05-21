#include <SpotLight.hpp>
#include <algorithm>
#include <string>
#include <vector>

std::vector<SpotLight*> SpotLight::instances = std::vector<SpotLight*>();
int SpotLight::LightsMatchingCount = 1;

SpotLight::SpotLight(){
    constant = 1.0f;
    linear = 0.22;
    quadratic = 0.20;
    radius = 20.f;
    smoothing = 0.1f;
    instances.push_back(this);
}

void SpotLight::BindToShader(Shader& shader, int id){
    std::string pos_key = "u_SpotLights[" + std::to_string(id) + "].position";
    std::string dir_key = "u_SpotLights[" + std::to_string(id) + "].direction";
    std::string col_key = "u_SpotLights[" + std::to_string(id) + "].color";
    std::string cut_key = "u_SpotLights[" + std::to_string(id) + "].cutoff";
    std::string smooth_key = "u_SpotLights[" + std::to_string(id) + "].smoothing_angle";
    std::string linear_key = "u_SpotLights[" + std::to_string(id) + "].linear";
    std::string constant_key = "u_SpotLights[" + std::to_string(id) + "].constant";
    std::string quadratic_key = "u_SpotLights[" + std::to_string(id) + "].quadratic";

    shader.SetVec3(pos_key.c_str(), position);
    shader.SetVec3(dir_key.c_str(), front);
    shader.SetVec3(col_key.c_str(), glm::vec3(1));
    shader.SetFloat(cut_key.c_str(), glm::cos(glm::radians(radius)));
    shader.SetFloat(smooth_key.c_str(), glm::cos(glm::radians((radius - (radius * std::clamp(smoothing, 0.0f, radius))))));
    shader.SetFloat(linear_key.c_str(), linear);
    shader.SetFloat(constant_key.c_str(), constant);
    shader.SetFloat(quadratic_key.c_str(), quadratic);
}

void SpotLight::ShaderSet(Shader& shader){
    for (int i = 0; i < LightsMatchingCount - glm::clamp(LightsMatchingCount - static_cast<int>(instances.capacity()), 0, LightsMatchingCount); i++){
        instances[i]->BindToShader(shader, i);
    }
}

void SpotLight::destroy(){
    instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());
}