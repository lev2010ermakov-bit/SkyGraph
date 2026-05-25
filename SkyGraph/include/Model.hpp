#pragma once

#include "Mesh.hpp"
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model{
    public:
        Model(const std::string path);
        void Draw(Material& mat);
    private:
        std::vector<Mesh> meshes;
        std::string directory;
        void loadFrom(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};