#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <Model.hpp>
#include <iostream>

Model::Model(std::string path){
    loadFrom(path);
}

void Model::Draw(Material& mat){
    for (auto m : meshes){
        m.Draw(mat);
    }
}

void Model::loadFrom(std::string path){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "Assimp error: " << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of("/"));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    for (unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex v;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        v.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        v.normal = vector;

        if (mesh->mTextureCoords[0]){
            glm::vec2 tex;
            tex.x = mesh->mTextureCoords[0][i].x;
            tex.y = mesh->mTextureCoords[0][i].y;
            v.texture_coords = tex;
        }
        else{
            v.texture_coords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(v);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}