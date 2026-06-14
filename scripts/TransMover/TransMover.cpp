#include "TransMover.hpp"

TransMover::TransMover(){

}
TransMover::TransMover(sky::Transformable& target){
    Target = &target;
}
void TransMover::Update(){
    if (Target == nullptr) return;

    buttPand -= sky::Time::deltaTime;

    if (buttPand < 0) 
        buttPand = 0;
    

    if (sky::Input::GetKey(sky::keycode::T) && buttPand <= 0){
        inWork = !inWork;
        if (inWork)
            std::cout << "TransMover Enabled" << std::endl;
        else
            std::cout << "TransMover Disabled" << std::endl;
        buttPand = 0.2f;
    }

    if (inWork){

        if (sky::Input::GetKey(sky::keycode::P)){
            currentOption = 0;
            std::cout << "Target.position" << std::endl;
        }
        if (sky::Input::GetKey(sky::keycode::R)){
            currentOption = 1;
            std::cout << "Target.rotation" << std::endl;
        }
        if (sky::Input::GetKey(sky::keycode::U)){
            currentOption = 2;
            std::cout << "Target.scale" << std::endl;
        }

        glm::vec3 input(0.f);
        input.x = sky::Input::GetKey(sky::keycode::W) ? 1 : (sky::Input::GetKey(sky::keycode::S) ? -1 : 0);
        input.y = sky::Input::GetKey(sky::keycode::D) ? 1 : (sky::Input::GetKey(sky::keycode::A) ? -1 : 0);
        input.z = sky::Input::GetKey(sky::keycode::E) ? 1 : (sky::Input::GetKey(sky::keycode::Q) ? -1 : 0);

        switch (currentOption){
            case 0:
                Target->position += input * sky::Time::deltaTime;
                break;
            case 1:
                Target->eulerAngles += input * sky::Time::deltaTime * 5.f;
                break;
            case 2:
                Target->scale += input * sky::Time::deltaTime;
                break;
        }

        if (sky::Input::GetKey(sky::keycode::L) && buttPand <= 0){
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
            buttPand = 0.2f;
        }
    }
}