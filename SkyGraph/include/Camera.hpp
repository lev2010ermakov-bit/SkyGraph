#pragma once

#include "Shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Transformable.hpp>

class Camera : public Transformable{
    public:
        Camera();
        Camera(float FOV, float XtoY, float near, float far);

        float Fov, Near, Far, XtoY;
        Color background;

        static Camera* main;

        glm::mat4 GetView();
        glm::mat4 GetProjection();
        static void SetMain(Camera& camera);
};