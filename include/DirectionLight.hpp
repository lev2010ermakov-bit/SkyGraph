#pragma once 

#include <SkyGraph.hpp>
#include <vector>

class DirectionLight : public LightSource{
    private:
        static std::vector<DirectionLight*> instances;
        static int LightsMatchingCount;

        void BindToShader(Shader& shader, int id) override;
        void destroy();
    public:
        DirectionLight();
        static void ShaderSet(Shader& shader);
};