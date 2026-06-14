#pragma once

#include "Mesh.hpp"
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace sky{
    class Model{
        public:
            Model(const std::string path);
            void Draw(Material& mat);
            std::vector<Mesh> meshes;
        private:
            std::string directory;
            void loadFrom(std::string path);
            void processNode(aiNode* node, const aiScene* scene);
            Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    };
}