#pragma once

#include <glm/glm.hpp>

const glm::vec3 World_up = glm::vec3(0.0f, 1.0f, 0.0f); 

class Transformable{
        static std::vector<Transformable*> instances;
        void destroy();
    public:
        Transformable();

        glm::vec3 scale;
        glm::vec3 position;
        glm::vec3 eulerAngles;
        
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;

        glm::mat4 GetModelMat();
        void UpdateLocalVectors();
        static void UpdateLocals();
};