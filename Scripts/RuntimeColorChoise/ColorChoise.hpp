#pragma once

#include <SkyGraph.hpp>
#include <GLFW/glfw3.h>

class ColorChoise{
    public:
        GLFWwindow* window;
        Material* material;
        float buttPand;
        bool colorDebug;
        int currentColDebug, currentColItem;

        ColorChoise();
        ColorChoise(GLFWwindow* wind, Material* mat);
        void Update(float deltaTime);
};