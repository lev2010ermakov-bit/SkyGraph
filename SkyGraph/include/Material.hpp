#pragma once

#include "Shader.hpp"

class Material{
    protected:
        Shader* shader;
    public:
        Color color;
        Material();
        virtual void Bind();
        virtual void SetShader(Shader& shader);
};