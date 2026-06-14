#pragma once

#include "LightSource.hpp"

namespace sky{
    class PointLight : public LightSource{
        public:
            float constant;
            float linear;
            float quadratic;
            PointLight();
            void BindToShader(Shader& shader, int id) override;
    };
}