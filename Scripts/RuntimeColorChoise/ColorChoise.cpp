#include "ColorChoise.hpp"
#include <iostream>

ColorChoise::ColorChoise(){

}

ColorChoise::ColorChoise(GLFWwindow* wind, Material* mat){
    window = wind;
    material = mat;
}

void ColorChoise::Update(float deltaTime){
    if (!window || !material) return;
    if (glfwGetKey(window, GLFW_KEY_T) && buttPand <= 0){
        colorDebug = !colorDebug;
        if (colorDebug) std::cout << "debug: Color Debuging turn ON" << std::endl;
        else            std::cout << "debug: Color Debuging turn OFF" << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) && buttPand <= 0 && colorDebug){
        currentColDebug--;
        if (currentColDebug < 0){
            currentColDebug = 2;
        }
        std::cout << "debug: color turned ";
        switch (currentColDebug){
            case 0: std::cout << "Ambient Color";  break;
            case 1: std::cout << "Difuse Color";   break;
            case 2: std::cout << "Specular Color"; break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_E) && buttPand <= 0 && colorDebug){
        currentColDebug++;
        if (currentColDebug > 2){
            currentColDebug = 0;
        }
        std::cout << "debug: color turned ";
        switch (currentColDebug){
            case 0: std::cout << "Ambient Color";  break;
            case 1: std::cout << "Difuse Color";   break;
            case 2: std::cout << "Specular Color"; break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_R) && buttPand <= 0 && colorDebug){
        currentColItem = 0;
        std::cout << "debug: color item turned ";
        switch (currentColItem){
            case 0: std::cout << "Red";   break;
            case 1: std::cout << "Green"; break;
            case 2: std::cout << "Blue";  break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_G) && buttPand <= 0 && colorDebug){
        currentColItem = 1;
        std::cout << "debug: color item turned ";
        switch (currentColItem){
            case 0: std::cout << "Red";   break;
            case 1: std::cout << "Green"; break;
            case 2: std::cout << "Blue";  break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_B) && buttPand <= 0 && colorDebug){
        currentColItem = 2;
        std::cout << "debug: Color item turned ";
        switch (currentColItem){
            case 0: std::cout << "Red";   break;
            case 1: std::cout << "Green"; break;
            case 2: std::cout << "Blue";  break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_EQUAL) && buttPand <= 0 && colorDebug){
        Color* CurrMatColor = &material->color;
        std::cout << "debug: ";
        switch (currentColItem){
            case 0: CurrMatColor->r += 5; std::cout << "r = " << round(CurrMatColor->r); break;
            case 1: CurrMatColor->g += 5; std::cout << "g = " << round(CurrMatColor->g); break;
            case 2: CurrMatColor->b += 5; std::cout << "b = " << round(CurrMatColor->b); break;
        }
        std::cout << std::endl;
        buttPand = 0.05f;
    }

    if (glfwGetKey(window, GLFW_KEY_MINUS) && buttPand <= 0 && colorDebug){
        Color* CurrMatColor = &material->color;
        std::cout << "debug: ";
        switch (currentColItem){
            case 0: CurrMatColor->r -= 5; std::cout << "r = " << round(CurrMatColor->r); break;
            case 1: CurrMatColor->g -= 5; std::cout << "g = " << round(CurrMatColor->g); break;
            case 2: CurrMatColor->b -= 5; std::cout << "b = " << round(CurrMatColor->b); break;
        }
        std::cout << std::endl;
        buttPand = 0.05f;
    }
    if (buttPand > 0)
        buttPand -= deltaTime;
}