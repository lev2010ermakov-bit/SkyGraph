#pragma once

#include <SkyGraph.hpp>

class TransMover{
    private:
        float buttPand;
        unsigned int currentOption;
    public:
        Transformable* Target;
        bool inWork;
        TransMover();
        TransMover(Transformable& target);
        void Update(float deltaTime, GLFWwindow* window);
};