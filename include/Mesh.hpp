#pragma once

#include <glm/glm.hpp>
#include "Texture.hpp"
#include "Material.hpp"
#include <vector>

namespace sky{
struct Vertex{
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture_coords;
    };

    class Mesh{
        public:
            std::vector<Vertex> vertexes;
            std::vector<unsigned int> indices;

            Mesh(std::vector<Vertex> vertexes, std::vector<unsigned int> indices);
            void Draw(Material& material);
        private:
            unsigned int VAO, VBO, EBO;
            void setupMesh();
    };
}