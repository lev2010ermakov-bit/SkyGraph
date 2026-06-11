#pragma once 

#include <SkyGraph.hpp>

class LitMat : public Material{
    public:
        Texture2D* DiffuseMap;
        Texture2D* SpecularMap;
        Texture2D* EmissionMap;
        Color ShadowColor = Color(20);
        float Roughness = 0.5f;
        float Shiness = 64.f;
        float MinLight = 0.1f;

        LitMat();
        LitMat(Shader& shader);
        void Bind() override;
};