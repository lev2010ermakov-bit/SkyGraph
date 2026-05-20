#pragma once 

#include "Shader.hpp"
#include "Transformable.hpp"

class LightSource : public Transformable{
    private:
        virtual void BindToShader(Shader& shader, int id);
    public:
        Color color;
        LightSource();
};