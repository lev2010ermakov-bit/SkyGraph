#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

namespace sky{
    //const glm::vec3 World_up = glm::vec3(0.0f, 1.0f, 0.0f);

    struct LocalVectors{
        LocalVectors(){
            up = glm::vec3(0.0f, 1.0f, 0.0f);
            front = glm::vec3(0, 0, 1);
            right = glm::vec3(1, 0, 0);
        }
        LocalVectors(glm::vec3 f, glm::vec3 r, glm::vec3 u){
            front = f;
            right = r;
            up = u;
        }
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;
    };

    class Transformable{
        private:
            Transformable* parent;
            std::vector<Transformable*> childs;
        public:
            Transformable();

            glm::vec3 scale;
            glm::vec3 position;
            glm::vec3 eulerAngles;

            void SetParent(Transformable* parent);
            void SetParent(Transformable& parent);
            Transformable* GetParent();

            LocalVectors getLocals();
            glm::mat4 GetModelMat();
    };
}