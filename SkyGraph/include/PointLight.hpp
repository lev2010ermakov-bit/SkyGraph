#pragma once

#include <SkyGraph.hpp>
#include <vector>

class PointLight : public LightSource{
    private:
        static std::vector<PointLight*> instances;
        static int LightsMatchingCount;

        void BindToShader(Shader& shader, int id) override;
        void destroy();
    public:
        float constant;
        float linear;
        float quadratic;
        PointLight();
        static void ShaderSet(Shader& shader);
};