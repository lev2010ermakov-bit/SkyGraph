#pragma once

#include "Component.hpp"
#include "Shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sky{
    class Camera : public Component{
        private:
            static float aspect;
        public:
            Camera(Object& object);
            Camera(float FOV, float near, float far, Object& object);

            float Fov, Near, Far;
            Color background;

            static Camera* main;

            glm::mat4 GetView();
            glm::mat4 GetProjection();
            static void SetMain(Camera& camera);
            static void UpdateAspect();
    };
}