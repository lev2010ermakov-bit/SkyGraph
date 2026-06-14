#include "Camera.hpp"
#include "Input.hpp"

namespace sky{
    Camera* Camera::main;
    float Camera::aspect;

    Camera::Camera(){
    
    }

    Camera::Camera(float fov, float near, float far){
        Fov = fov;
        Near = near;
        Far = far;
    }
    glm::mat4 Camera::GetView(){
        LocalVectors local = getLocals();
        return glm::lookAt(position, position + local.front, local.up);
    }

    glm::mat4 Camera::GetProjection(){
        return glm::perspective(glm::radians(Fov), aspect, Near, Far);
    }

    void Camera::SetMain(Camera& camera){
        main = &camera;
    }

    void Camera::UpdateAspect(){
        glm::vec2 winSize = Input::GetWindowSize();
        aspect = winSize.x/winSize.y;
    }
}