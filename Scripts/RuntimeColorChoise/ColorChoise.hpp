#pragma once

#include <SkyGraph.hpp>
#include <GLFW/glfw3.h>

class ColorChoise{
    public:
        GLFWwindow* window;
        sMaterial* shaderMat;
        Shader* shader;
        float buttPand;
        bool colorDebug;
        int currentColDebug, currentColItem;

        ColorChoise();
        ColorChoise(GLFWwindow* wind, sMaterial* mat, Shader* shade);
        void Update(float deltaTime);
};