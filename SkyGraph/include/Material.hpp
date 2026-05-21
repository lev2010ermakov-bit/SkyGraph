#pragma once

#include <SkyGraph.hpp>

class Material{
    private:
        Shader& shader;
    public:
        Color color;
        Material(Shader& shader);
};