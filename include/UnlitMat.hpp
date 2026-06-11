#pragma once 

#include <SkyGraph.hpp>

class UnlitMat : public Material{
    public:
        Texture2D* texture;
        UnlitMat();
        UnlitMat(Shader& shader);
        void Bind() override;
};