#pragma once

#include <SkyGraph.hpp>
#include <vector>

class SpotLight : public LightSource{
    private:
        static std::vector<SpotLight*> instances;
        static int LightsMatchingCount;

        void BindToShader(Shader& shader, int id) override;
        void destroy();
    public:
        float constant;
        float linear;
        float quadratic;

        float radius;
        float smoothing;
        SpotLight();
        static void ShaderSet(Shader& shader);
};