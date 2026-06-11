#include <Time.hpp>
#include <iostream>
#include <GLFW/glfw3.h>


namespace sk{
    float Time::lastTime = 0;
    float Time::deltaTime = 0;
    Time* Time::instance = nullptr;

    Time::Time(){
        if (instance == nullptr)
            instance = this;
        else{
            std::cout << "Time had already created before!\n";
            delete this;
        }
    }

    void Time::Init(){
        new Time();
    }

    void Time::Update(){
        deltaTime = static_cast<float>(glfwGetTime()) - lastTime;
        lastTime = static_cast<float>(glfwGetTime());
    }
}