#include <PointLight.hpp>
#include <string>

namespace sky{

    PointLight::PointLight(){
        constant = 1.0f;
        linear = 0.22;
        quadratic = 0.20;
    }

    void PointLight::BindToShader(Shader& shader, int id){
        std::string pos_key = "u_PointLights[" + std::to_string(id) + "].position";
        std::string col_key = "u_PointLights[" + std::to_string(id) + "].color";
        std::string linear_key = "u_PointLights[" + std::to_string(id) + "].linear";
        std::string constant_key = "u_PointLights[" + std::to_string(id) + "].constant";
        std::string quadratic_key = "u_PointLights[" + std::to_string(id) + "].quadratic";

        shader.SetVec3(pos_key.c_str(), position);
        shader.SetVec3(col_key.c_str(), color.glCol3());
        shader.SetFloat(linear_key.c_str(), linear);
        shader.SetFloat(constant_key.c_str(), constant);
        shader.SetFloat(quadratic_key.c_str(), quadratic);
    }
}