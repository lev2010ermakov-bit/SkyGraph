#include <Object.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


namespace sk{
    // ---------- Static Fields ---------- //

    Object* Object::scene = nullptr;


    // ---------- Constructors ---------- //

    Object::Object(){
        if (scene == nullptr)
            scene = new Object();

        position = glm::vec3(0.0f);
        eulerAngles = glm::vec3(0.0f);
        scale = glm::vec3(1.0f);

        UpdateLocalVectors();
    }


    // ---------- Transformation Controls ---------- //

    glm::mat4 Object::GetModelMat(){
        glm::mat4 res = glm::mat4(1);

        res = glm::translate(res, glm::vec3(position.x, -position.y, position.z));
        res = glm::rotate(res, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
        res = glm::rotate(res, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
        res = glm::rotate(res, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
        res = glm::scale(res, scale);

        if (parent != scene)
            return res;
        else
            return parent->GetModelMat() * res;
    }

    void Object::UpdateLocalVectors(){
        glm::vec3 dir;
        dir.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
        dir.y = sin(glm::radians(eulerAngles.x));
        dir.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
        front = glm::normalize(dir);
        right = glm::normalize(glm::cross(front, World_up));
        up = glm::normalize(glm::cross(front, right));
    }


    // ----------- Parent Control ---------- //

    void Object::SetParent(Object& p){
        parent = &p;
    }

    void Object::SetParent(Object* p){
        if (p != nullptr)
            parent = p;
        else
            parent = scene;
    }

    Object* Object::GetParent(){
        return parent;
    }


    // ---------- Childrens Control ---------- //

    void Object::AddChild(Object child){
        child.SetParent(this);
        childs.push_back(child);
    }

    Object& Object::GetChild(int id){
        if (id < childs.capacity()) 
            return childs[id];
        else{
            std::cout << "Can not get child " << id << " cause id is over childs count! returned this object\n";
            return *this;
        }
    }
}