#include "Camera.hpp"

Camera* Camera::main;

Camera::Camera(){
    
}

Camera::Camera(float fov, float xtoy, float near, float far){
    Fov = fov;
    Near = near;
    Far = far;
    XtoY = xtoy;
}
glm::mat4 Camera::GetView(){
    LocalVectors local = getLocals();
    return glm::lookAt(position, position + local.front, local.up);
}

glm::mat4 Camera::GetProjection(){
    return glm::perspective(glm::radians(Fov), XtoY, Near, Far);
}

void Camera::SetMain(Camera& camera){
    main = &camera;
}