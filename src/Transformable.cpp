#include <Transformable.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>

namespace sky{
    // ----------   CONSTRUCTORS   ---------- //
    Transformable::Transformable(){
        scale = glm::vec3(1);
        position = glm::vec3(0);
        eulerAngles = glm::vec3(0);
        parent = nullptr;
    }


    // ----------   OUTPUT FUNCTIONS ---------- //
    glm::mat4 Transformable::GetModelMat(){
        glm::mat4 res = glm::mat4(1);

        res = glm::translate(res, position);
        res = glm::rotate(res, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
        res = glm::rotate(res, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
        res = glm::rotate(res, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
        res = glm::scale(res, scale);

        if (parent == nullptr)
            return res;
        else
            return parent->GetModelMat() * res ;
    }


    // ----------   SYSTEM FUNCTIONS   ---------- //
    LocalVectors Transformable::getLocals(){
        LocalVectors res;
        glm::vec3 dir;
        dir.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
        dir.y = sin(glm::radians(eulerAngles.x));
        dir.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
        res.front = glm::normalize(dir);
        res.right = glm::normalize(glm::cross(res.front, glm::vec3(0.0f, 1.0f, 0.0f)));
        res.up = glm::normalize(glm::cross(res.front, res.right));
        return res;
    }

    void Transformable::SetParent(Transformable* p){
        parent = p;
    }

    void Transformable::SetParent(Transformable& p){
        parent = &p;
    }

    Transformable* Transformable::GetParent(){
        return parent;
    }
}