#include <Camera.hpp>
#include <GLFW/glfw3.h>
#include <Input.hpp>
#include <iostream>

namespace sky{
    glm::vec2 Input::lastPointerPos = glm::vec2();
    glm::vec2 Input::WindowSize = glm::vec2();
    glm::vec2 Input::PointerPos = glm::vec2();
    GLFWwindow* Input::window = nullptr;
    Input* Input::instance = nullptr;

    Input::Input(GLFWwindow* w){
        if (instance != nullptr){
            delete this;
            return;
        }

        if (w == nullptr){
            std::cerr << "Invalid Window Pointer\n";
            return;
        }

        instance = this;
        window = w;
    }

    void Input::frame_buffer_size_callback(GLFWwindow* w, int width, int height){
        WindowSize.x = width;
        WindowSize.y = height;
        Camera::UpdateAspect();
    }

    void Input::cursor_position_callback(GLFWwindow *w, double x, double y){
        lastPointerPos = PointerPos;
        PointerPos = glm::vec2(x, y);
    }

    bool Input::GetKey(keycode key){
        return glfwGetKey(window, key);
    }

    glm::vec2 Input::GetMouseDeltaPosition(){
        glm::vec2 res;
        res.x = PointerPos.x - lastPointerPos.x;
        res.y = lastPointerPos.y - PointerPos.y;
        lastPointerPos = PointerPos;
        return res;
    }

    glm::vec2 Input::GetMousePosition(){
        return PointerPos;
    }

    glm::vec2 Input::GetWindowSize(){
        return WindowSize;
    }

    void Input::SetCursorMode(cursMode mode){
        glfwSetInputMode(window, GLFW_CURSOR, mode);
    }
}