#pragma once 

#include "Material.hpp"

namespace sky{
    class UnlitMat : public Material{
        public:
            Texture2D* texture;
            UnlitMat();
            UnlitMat(Shader& shader);
            void Bind() override;
    };
}