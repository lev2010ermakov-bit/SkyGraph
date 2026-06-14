#pragma once

#include <glad/glad.h>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"
#include "Camera.hpp"
#include "LightSource.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "DirectionLight.hpp"
#include "Material.hpp"
#include "UnlitMat.hpp"
#include "LitMat.hpp"
#include "Model.hpp"
#include "Mesh.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Time.hpp"
#include "Input.hpp"

namespace sky{
    void InitWindow(const char* title, unsigned int width, unsigned int height);
    bool WindowShouldClose();

    void ClearWindow(Color color);
    void ShowWindow();
}