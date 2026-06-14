#include "CameraMover.hpp"

CameraMover::CameraMover(){

}

void CameraMover::Update(){
    if (camera == nullptr) return;
    keyboard_moving();
    mouse_moving();
}

void CameraMover::keyboard_moving(){
    sky::LocalVectors camLocals = camera->getLocals();
    if (sky::Input::GetKey(sky::keycode::W))
    {
        camera->position += camLocals.front * sky::Time::deltaTime * 10.f;
    }
    if (sky::Input::GetKey(sky::keycode::S))
    {
        camera->position -= camLocals.front * sky::Time::deltaTime * 10.f;
    }
    if (sky::Input::GetKey(sky::keycode::A))
    {
        camera->position += camLocals.right * 10.f * sky::Time::deltaTime;
    }
    if (sky::Input::GetKey(sky::keycode::D))
    {
        camera->position -= camLocals.right * 10.f * sky::Time::deltaTime;
    }
    if (sky::Input::GetKey(sky::keycode::ESC) && buttPand <= 0)
    {
        if (CursHiden)
            sky::Input::SetCursorMode(sky::cursMode::NORMAL);
        else
        {
            sky::Input::SetCursorMode(sky::cursMode::DISABLED);
            firstMouse = true;
        }
        CursHiden = CursHiden ? false : true;
        buttPand = 0.2f;
    }
}

void CameraMover::mouse_moving(){
    if (firstMouse)
    {
        firstMouse = false;
    }

    glm::vec2 mouse_delta = sky::Input::GetMouseDeltaPosition() * mouse_sence;

    if (CursHiden)
    {
        camera->eulerAngles.y -= mouse_delta.x;
        camera->eulerAngles.x -= mouse_delta.y;
    }
    if (camera->eulerAngles.x >= 89.999f)
        camera->eulerAngles.x = 89.999f;
    else if (camera->eulerAngles.x <= -89.999f)
        camera->eulerAngles.x = -89.999f;
}