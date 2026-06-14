#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace sky{
    enum keycode{
        Q = GLFW_KEY_Q,
        W = GLFW_KEY_W,
        E = GLFW_KEY_E,
        R = GLFW_KEY_R,
        T = GLFW_KEY_T,
        Y = GLFW_KEY_Y,
        U = GLFW_KEY_U,
        I = GLFW_KEY_I,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        Z = GLFW_KEY_Z,
        X = GLFW_KEY_X,
        C = GLFW_KEY_C,
        V = GLFW_KEY_V,
        B = GLFW_KEY_B,
        N = GLFW_KEY_N,
        M = GLFW_KEY_M,

        ESC = GLFW_KEY_ESCAPE,
        TAB = GLFW_KEY_TAB
    };

    enum cursMode{
        NORMAL = GLFW_CURSOR_NORMAL,
        DISABLED = GLFW_CURSOR_DISABLED,
    };

    class Input{
        private:
            static GLFWwindow* window;
            static Input* instance;
            static glm::vec2 WindowSize;
            static glm::vec2 PointerPos;
            static glm::vec2 lastPointerPos;
        public:
            Input(GLFWwindow* window);

            static void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
            static void cursor_position_callback(GLFWwindow* window, double x, double y);
            static glm::vec2 GetMousePosition();
            static glm::vec2 GetMouseDeltaPosition();
            static glm::vec2 GetWindowSize();

            static bool GetKey(keycode key);
            static void SetCursorMode(cursMode mode);
    };
}