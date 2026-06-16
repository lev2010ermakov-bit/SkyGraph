#pragma once

#include <SkyGraph.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum direction{
    forward,
    backward,
    right,
    left,
    down,
    up
};

class CameraMover{
    public:
        CameraMover();
        void Update();
        sky::Object* camera;
        bool firstMouse = true, CursHiden = true;
        float mouse_sence = 0.1f, buttPand;
    private:
        void keyboard_moving();
        void mouse_moving();
};