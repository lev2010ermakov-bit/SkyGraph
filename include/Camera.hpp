#pragma once

#include "Shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformable.hpp"

namespace sky{
    class Camera : public Transformable{
        private:
            static float aspect;
        public:
            Camera();
            Camera(float FOV, float near, float far);

            float Fov, Near, Far;
            Color background;

            static Camera* main;

            glm::mat4 GetView();
            glm::mat4 GetProjection();
            static void SetMain(Camera& camera);
            static void UpdateAspect();
    };
}