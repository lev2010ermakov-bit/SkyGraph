#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>
namespace sky{
enum TextureType{
    DiffuseMap,
    SpecularMap,
    EmmisionMap
};

struct Texture2D{
        unsigned int ID;
        TextureType type;
        GLint ColAttrib;
        GLint TextureFilter;
        int width, height, nrChanels;
        std::string FilePath;

        Texture2D();
        Texture2D(const char* path, GLint colorAttrib, GLint textureFilter);
        void loadFromFile(const char* path, GLint colorAttrib, GLint textureFilter);
        void Bind();

        Texture2D& operator=(const Texture2D& other);
        Texture2D& operator=(Texture2D&& other);
    };
}