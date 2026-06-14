#pragma once

#include "LightSource.hpp"

namespace sky{
    class SpotLight : public LightSource{
        public:
            float constant;
            float linear;
            float quadratic;

            float radius;
            float smoothing;
            SpotLight();
            void BindToShader(Shader& shader, int id) override;
    };
}