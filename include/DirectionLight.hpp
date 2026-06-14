#pragma once 

#include "LightSource.hpp"

namespace sky{
    class DirectionLight : public LightSource{
        public:
            DirectionLight();
            void BindToShader(Shader& shader, int id) override;
    };
}