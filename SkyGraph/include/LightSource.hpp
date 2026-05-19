#pragma once 

#include "Shader.hpp"
#include "Transformable.hpp"

class LightSource : public Transformable{
    public:
        Color color;
        LightSource();
};