#include "Camera.hpp"
#include "Input.hpp"
#include "Object.hpp"

namespace sky{
    Camera* Camera::main;
    float Camera::aspect;

    Camera::Camera(Object& o) : Component(o){
    
    }

    Camera::Camera(float fov, float near, float far, Object& o) : Component(o){
        Fov = fov;
        Near = near;
        Far = far;
    }
    glm::mat4 Camera::GetView(){
        return glm::lookAt(thisObject.position, thisObject.position + thisObject.front(), thisObject.up());
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