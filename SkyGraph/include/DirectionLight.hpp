#pragma once 

#include "LightSource.hpp"
#include "Shader.hpp"
#include <SkyGraph.hpp>
#include <vector>

class DirectionLight : public LightSource{
    private:
        static std::vector<DirectionLight*> instances;
        void BindToShader(Shader* s, int id);
        bool destroy = false;
    public:
        DirectionLight();
        static void SetDirToShader(Shader* shader);
};