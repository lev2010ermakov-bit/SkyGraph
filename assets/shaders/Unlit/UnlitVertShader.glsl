#version 330 core

layout (location=0) in vec3 aPos;
layout (location=2) in vec2 aTex;

out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main(){
    TexCoords = aTex;
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos.xyz, 1.0f);
}