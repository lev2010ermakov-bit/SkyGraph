#include "TransMover.hpp"

TransMover::TransMover(){

}
TransMover::TransMover(Transformable& target){
    Target = &target;
}
void TransMover::Update(float deltaTime, GLFWwindow* window){
    if (Target == nullptr) return;

    buttPand -= deltaTime;

    if (buttPand < 0) 
        buttPand = 0;
    

    if (glfwGetKey(window, GLFW_KEY_T) && buttPand <= 0){
        inWork = !inWork;
        if (inWork)
            std::cout << "TransMover Enabled" << std::endl;
        else
            std::cout << "TransMover Disabled" << std::endl;
        buttPand = 0.2f;
    }

    if (inWork){

        if (glfwGetKey(window, GLFW_KEY_P)){
            currentOption = 0;
            std::cout << "Target.position" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_R)){
            currentOption = 1;
            std::cout << "Target.rotation" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_U)){
            currentOption = 2;
            std::cout << "Target.scale" << std::endl;
        }

        glm::vec3 input(0.f);
        input.x = glfwGetKey(window, GLFW_KEY_W) ? 1 : (glfwGetKey(window, GLFW_KEY_S) ? -1 : 0);
        input.y = glfwGetKey(window, GLFW_KEY_D) ? 1 : (glfwGetKey(window, GLFW_KEY_A) ? -1 : 0);
        input.z = glfwGetKey(window, GLFW_KEY_E) ? 1 : (glfwGetKey(window, GLFW_KEY_Q) ? -1 : 0);

        switch (currentOption){
            case 0:
                Target->position += input * deltaTime;
                break;
            case 1:
                Target->eulerAngles += input * deltaTime * 5.f;
                break;
            case 2:
                Target->scale += input * deltaTime;
                break;
        }

        if (glfwGetKey(window, GLFW_KEY_L)){
            switch (currentOption){
                case 0:
                    std::cout << "Position" << " x " << Target->position.x << " y " << Target->position.y << " z " << Target->position.z << std::endl;
                    break;
                case 1:
                    std::cout << "Rotation" << " x " << Target->eulerAngles.x << " y " << Target->eulerAngles.y << " z " << Target->eulerAngles.z << std::endl;
                    break;
                case 2:
                    std::cout << "Scale" << " x " << Target->scale.x << " y " << Target->scale.y << " z " << Target->scale.z << std::endl;
                    break;
            }
        }
    }
}