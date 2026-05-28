#include <Transformable.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>


// ----------   CONSTRUCTORS   ---------- //
Transformable::Transformable(){
    scale = glm::vec3(1);
    position = glm::vec3(0);
    eulerAngles = glm::vec3(0);
}


// ----------   OUTPUT FUNCTIONS ---------- //
glm::mat4 Transformable::GetModelMat(){
    glm::mat4 res = glm::mat4(1);

    res = glm::translate(res, position);
    res = glm::rotate(res, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
    res = glm::rotate(res, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
    res = glm::rotate(res, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
    res = glm::scale(res, scale);

    return res;
}


// ----------   SYSTEM FUNCTIONS   ---------- //
LocalVectors Transformable::getLocals(){
    LocalVectors res;
    glm::vec3 dir;
    dir.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
    dir.y = sin(glm::radians(eulerAngles.x));
    dir.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
    res.front = glm::normalize(dir);
    res.right = glm::normalize(glm::cross(res.front, World_up));
    res.up = glm::normalize(glm::cross(res.front, res.right));
    return res;
}