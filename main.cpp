#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scripts/Loader/Loader.hpp"
#include "Scripts/CameraMover/CameraMover.hpp"

#include <SkyGraph.hpp>

float lastTime;
float deltaTime;

bool colorDebug;
int currentColDebug;
int currentColItem;

Shader LitShader;
Shader UnlitShader;

UnlitMat PointMat;
UnlitMat DirMat;
UnlitMat Dir2Mat;

LitMat LightMat;

DirectionLight dir;
DirectionLight dir2;
PointLight point;
SpotLight flashlight;
bool flashlightTurn = true;

Camera camera;
CameraMover mover;

void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera.XtoY = (float)width/(float)height;
    mover.lastx = (float)width/2;
    mover.lasty = (float)height/2; 
}

void curs_callback(GLFWwindow* wind, double x, double y){
    mover.onCursPosChanged(wind, x, y);
}

int main(int agrc, char *agrv[])
{
    camera = Camera(75, 800.f/600.f, 0.1f, 10000.f);  // Initializing camera class
    Camera::SetMain(camera);                                            // Set new camera as a main  
    camera.position = glm::vec3(-3.31473, -1.567f, 6.05006f);
    camera.eulerAngles = glm::vec3(14.9043f, -61.7206f, 0.0f);
    camera.background = Color(45, 138, 189);    //beauty blue color
    //camera.background = Color(209, 46, 33);    //beauty red color
    //camera.background = Color(20);

    curr_agrv = agrv[0];
    glfwInit();                                                     // Initializing a glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Set version of programm context to 3 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  //
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Set Profile of programm context to core

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL 2D Render", NULL, NULL);    // Create a small window
    glfwMakeContextCurrent(window);                                                     // Give a program focuse to window
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);                 // Set a window scaling callback

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))                            // Load glad function uses a glfw
    {
        std::cout << "Failed To init glad" << std::endl;                                // error log
    }

    mover = CameraMover(camera, *window);  // Create a class that moves the camera

    glEnable(GL_DEPTH_TEST);    // enable an OpenGL depth test 

    Model cube(GetFullPath("Assets/cube.obj"));

    frame_buffer_size_callback(window, 800, 600);                                               // calling a window scaling callback to setup our program to res 800x600
    glfwSwapInterval((float)1 / (float)144);                                                        // Setting Vsync for 144 hz monitor

    bool polygon;
    float buttPand;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, curs_callback);

    Texture2D PugTex(GetFullPath("SkyGraph/assets/Textures/PugImage.png").c_str(), GL_RGBA, GL_LINEAR);         // Loading a Textures
    Texture2D CatSpec(GetFullPath("SkyGraph/assets/Textures/catSpecular.png").c_str(), GL_RGBA, GL_LINEAR);     //
    Texture2D EmissionMap(GetFullPath("SkyGraph/assets/Textures/EmissionMap.jpg").c_str(), GL_RGB, GL_LINEAR);  //
    Texture2D CatTex(GetFullPath("SkyGraph/assets/Textures/catImage.jpg").c_str(), GL_RGB, GL_LINEAR);          //
    Texture2D RockTex(GetFullPath("SkyGraph/assets/Textures/rockImage.jpg").c_str(), GL_RGB, GL_LINEAR);        // 
    Texture2D CarTex(GetFullPath("Assets/textures/gltf_embedded_0.png").c_str(), GL_RGBA, GL_NEAREST);

    LitShader.Setup(GetFullPath("SkyGraph/assets/Shaders/Lit/VertShader.glsl").c_str(),
                 GetFullPath("SkyGraph/assets/Shaders/Lit/FragShader.glsl").c_str());
    UnlitShader.Setup(GetFullPath("SkyGraph/assets/Shaders/Unlit/UnlitVertShader.glsl").c_str(), 
                     GetFullPath("SkyGraph/assets/Shaders/Unlit/UnlitFragShader.glsl").c_str());

    Transformable carTransformable;
    carTransformable.eulerAngles = glm::vec3(-180, 180, 0);
    Model carModel(GetFullPath("Assets/source/Untitled.obj"));

    LightMat.SetShader(LitShader);
    LightMat.color = Color(255);

    PointMat.SetShader(UnlitShader);

    DirMat.SetShader(UnlitShader);
    Dir2Mat.SetShader(UnlitShader);

    LightMat.Shiness = 256.f;
    LightMat.Roughness = 1.f;
    LightMat.ShadowColor = Color(50);
    LightMat.DiffuseMap = &CarTex;

    dir.color = Color(255.0f);
    dir.eulerAngles.y = 90.f;
    dir.eulerAngles.x = 20;
    dir.scale = glm::vec3(0.3f);
    dir.position -= dir.getLocals().front * 3.f;

    dir2.eulerAngles.y = -90;
    dir2.eulerAngles.x = 20;
    dir2.color = Color(0.9569 * 255, 0.6549 * 255, 0.1686 * 255);
    dir2.scale = glm::vec3(0.3f);
    dir2.position -= dir2.getLocals().front * 3.f;

    point.color = Color(0);
    point.position = glm::vec3(7);
    point.constant = 1.0f;
    point.linear = 0.09f;
    point.quadratic = 0.032f;

    point.position = glm::vec3(0.0f);
    point.scale = glm::vec3(0.1f);

    flashlight.color = Color(255);
    flashlight.radius = 30.f;
    flashlight.smoothing = 0.1f;

    flashlight.constant = 1.0f;
    flashlight.linear = 0.22f;
    flashlight.quadratic = 0.20f;

    flashlight.position = camera.position;
    flashlight.eulerAngles = camera.eulerAngles;

    DirMat.color = dir.color;
    Dir2Mat.color = dir2.color;
    PointMat.color = point.color;

    Transformable child, parent;
    child.scale = glm::vec3(0.5f);
    parent.scale = glm::vec3(0.4f);
    child.SetParent(parent);    
    parent.position.x = 8;
    child.position.y = 2;

    while (!glfwWindowShouldClose(window))
    {
        DirectionLight::ShaderSet(LitShader);
        PointLight::ShaderSet(LitShader);
        SpotLight::ShaderSet(LitShader);

        glClearColor(camera.background.glCol4().r, camera.background.glCol4().g, camera.background.glCol4().b, camera.background.glCol4().a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        mover.Update(deltaTime);
        

        flashlight.position = camera.position;
        flashlight.eulerAngles = camera.eulerAngles;

        LightMat.Bind();
        LitShader.SetVec3("camPos", Camera::main->position);                                               // Set a view pos
        LitShader.SetMat4("u_Model", carTransformable.GetModelMat());                                              // Set Transformation matrix to shader
        LitShader.SetMat4("u_View", Camera::main->GetView());                                              // Set View matrix to make a camera moving effect
        LitShader.SetMat4("u_Projection", Camera::main->GetProjection());
        carModel.Draw(LightMat);

        PointMat.Bind();
        UnlitShader.SetMat4("u_Model", point.GetModelMat());
        UnlitShader.SetMat4("u_View", Camera::main->GetView());
        UnlitShader.SetMat4("u_Projection", Camera::main->GetProjection());
        cube.Draw(PointMat);

        DirMat.Bind();
        UnlitShader.SetMat4("u_Model", dir.GetModelMat());
        cube.Draw(DirMat);

        Dir2Mat.Bind();
        UnlitShader.SetMat4("u_Model", dir2.GetModelMat());
        cube.Draw(Dir2Mat);

        DirMat.Bind();
        UnlitShader.SetMat4("u_Model", parent.GetModelMat());
        cube.Draw(DirMat);

        Dir2Mat.Bind();
        UnlitShader.SetMat4("u_Model", child.GetModelMat());
        cube.Draw(Dir2Mat); 

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (buttPand > 0)
            buttPand -= deltaTime;

        if (glfwGetKey(window, GLFW_KEY_TAB) && buttPand <= 0)     // Switching a polygon mode
        {                                                               // 
            polygon = !polygon;                                         //
            GLint mode = polygon ? GL_LINE : GL_FILL;
            glPolygonMode(GL_FRONT_AND_BACK, mode);
            buttPand = 0.2f;                                            //
        }
        /*
        if (glfwGetKey(window, GLFW_KEY_1) && buttPand <= 0)    // Switching to Cat texture
        {
            LightMat.color = Color(255);
            LightMat.DiffuseMap = &CatTex;
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_2) && buttPand <= 0)    // Switching to Pug texture
        {
            LightMat.color = Color(255);
            LightMat.DiffuseMap = &PugTex;                       //
            buttPand = 0.2f;                                         //
        }                                                            //

        if (glfwGetKey(window, GLFW_KEY_3) && buttPand <= 0){
            LightMat.color = Color(255);
            LightMat.DiffuseMap = &RockTex;
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_4) && buttPand <= 0){   // Switching to Monochrome mode
            LightMat.color = Color(116, 155, 63);
            LightMat.DiffuseMap = nullptr;
            buttPand = 0.2f;                                        //
        }                                                           //
        */
        if (glfwGetKey(window, GLFW_KEY_F) && buttPand <= 0){
            if (flashlightTurn){
                flashlight.color = Color(0);
            }
            else{
                flashlight.color = Color(255);
            }
            flashlightTurn = !flashlightTurn;
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_L) && buttPand <= 0){
            std::cout << "pos: " << camera.position.x << " " << camera.position.y << " " << camera.position.z << std::endl;
            std::cout << "rot: " << camera.eulerAngles.x << " " << camera.eulerAngles.y << " " << camera.eulerAngles.z << std::endl;
            buttPand = 0.2f;
        }

        deltaTime = (float)glfwGetTime() - lastTime;                // Calculation of time beetween frames
        lastTime = (float)glfwGetTime();                            //
    }
    return 0;
}