#include <SkyGraph.hpp>

namespace sky{
    GLFWwindow* window = nullptr;

    void InitWindow(const char* title, unsigned int width, unsigned int height){
        glfwInit();                                                     // Initializing a glfw
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Set version of programm context to 3 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  //
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Set Profile of programm context to core

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        glfwMakeContextCurrent(window);                                                     // Give a program focuse to window
        glfwSetFramebufferSizeCallback(window, Input::frame_buffer_size_callback);                 // Set a window scaling callback

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))                            // Load glad function uses a glfw
        {
            std::cout << "Failed To init glad" << std::endl;                                // error log
        }

        glEnable(GL_DEPTH_TEST);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, Input::cursor_position_callback);
        Input::frame_buffer_size_callback(window, 800, 600);

        new Input(window);
        new Time();
    }

    bool WindowShouldClose(){
        return glfwWindowShouldClose(window);
    }

    void ClearWindow(Color color){
        glm::vec4 glcol = color.glCol4();
        glClearColor(glcol.r, glcol.g, glcol.b, glcol.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void ShowWindow(){
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}