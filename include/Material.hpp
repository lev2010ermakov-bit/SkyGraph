#pragma once

#include "Shader.hpp"

namespace sky{
    class Material{
        protected:
            Shader* shader;
        public:
            Color color;
            Material();
            virtual void Bind();
            virtual void SetShader(Shader& shader);
    };
}