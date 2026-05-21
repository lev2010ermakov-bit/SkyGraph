#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "cubeData.h"
#include "Scripts/Loader/Loader.hpp"
#include "Scripts/CameraMover/CameraMover.hpp"
#include "Scripts/RuntimeColorChoise/ColorChoise.hpp"

#include <SkyGraph.hpp>

float lastTime;
float deltaTime;

bool colorDebug;
int currentColDebug;
int currentColItem;

Shader shader;
Shader LampShader;

ColorChoise colChoiser;

sMaterial shaderMat;

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
    //camera.background = Color(45, 138, 189);    //beauty blue color
    //camera.background = Color(209, 46, 33);    //beauty red color
    camera.background = Color(20);

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

    unsigned int VertexBufferObject, VertexArrayObject, LightVertexArrayObject, LightVertexBufferObject;

    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vtn_cube_vertexes), vtn_cube_vertexes, GL_STATIC_DRAW);


    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &LightVertexArrayObject);
    glBindVertexArray(LightVertexArrayObject);
    glGenBuffers(1, &LightVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, LightVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_cube_vertexes), v_cube_vertexes, GL_STATIC_DRAW);
    glBindVertexArray(LightVertexArrayObject);                                                                           //
    glBindBuffer(GL_ARRAY_BUFFER, LightVertexBufferObject);                                                      //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);  //
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    frame_buffer_size_callback(window, 800, 600);                                               // calling a window scaling callback to setup our program to res 800x600
    glfwSwapInterval((float)1 / (float)144);                                                        // Setting Vsync for 144 hz monitor

    std::vector<Transformable> cubes = std::vector<Transformable>(4);

    cubes[0].position = glm::vec3(-1.5f, 1.f, 1.f);
    cubes[0].scale = glm::vec3(1.1f);

    cubes[1].position = glm::vec3(3.f, -0.7f, -2.f);
    cubes[1].scale = glm::vec3(2.f);

    cubes[2].position = glm::vec3(0.8f, 4.f, -2.f);
    cubes[2].scale = glm::vec3(0.7f);

    cubes[3].position = glm::vec3(15.f, 0, 10.f);
    cubes[3].scale = glm::vec3(1.f);

    bool polygon;
    float buttPand;

    float rot;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, curs_callback);

    colChoiser.window = window;
    colChoiser.shader = &shader;
    colChoiser.shaderMat = &shaderMat;

    std::shared_ptr<Texture2D> PugTex = std::make_shared<Texture2D>(GetFullPath("SkyGraph/assets/Textures/PugImage.png").c_str(), GL_RGBA);         // Loading a Textures
    std::shared_ptr<Texture2D> CatSpec = std::make_shared<Texture2D>(GetFullPath("SkyGraph/assets/Textures/catSpecular.png").c_str(), GL_RGBA);     //
    std::shared_ptr<Texture2D> EmissionMap = std::make_shared<Texture2D>(GetFullPath("SkyGraph/assets/Textures/EmissionMap.jpg").c_str(), GL_RGB);
    std::shared_ptr<Texture2D> CatTex = std::make_shared<Texture2D>(GetFullPath("SkyGraph/assets/Textures/catImage.jpg").c_str(), GL_RGB);          //
    std::shared_ptr<Texture2D> RockTex = std::make_shared<Texture2D>(GetFullPath("SkyGraph/assets/Textures/rockImage.jpg").c_str(), GL_RGB);        // 

    shader.Setup(GetFullPath("SkyGraph/assets/Shaders/Lit/VertShader.glsl").c_str(),
                 GetFullPath("SkyGraph/assets/Shaders/Lit/FragShader.glsl").c_str());
    shader.color = Color(116, 155, 63);

    LampShader.Setup(GetFullPath("SkyGraph/assets/Shaders/Unlit/UnlitVertShader.glsl").c_str(), 
                     GetFullPath("SkyGraph/assets/Shaders/Unlit/UnlitFragShader.glsl").c_str());
    LampShader.color = Color(255, 255, 255);

    shaderMat.AmbientColor = glm::vec3(1.0f);
    shaderMat.DifuseColor = glm::vec3(1.0f);
    shaderMat.SpecularColor = glm::vec3(1.0f);
    shaderMat.Shiness = 256.f;

    shader.UseTexture = true;

    shader.SetColor("u_Material.DiffuseColor", shader.color);
    shader.SetVec3("u_Material.ShadowColor", glm::vec3(0.3f));
    shader.DiffuseMap = PugTex;
    shader.SetFloat("u_Material.minLight", 0.4f);
    shader.SetFloat("u_Material.Specular", 0.5f);
    shader.SetFloat("u_Material.Shiness", shaderMat.Shiness);

    dir.color = Color(255.0f);
    dir.eulerAngles.y = 90.f;
    dir.eulerAngles.x = 20;
    dir.scale = glm::vec3(0.3f);
    Transformable::UpdateLocals();
    dir.position -= dir.front * 3.f;

    dir2.eulerAngles.y = -90;
    dir2.eulerAngles.x = 20;
    dir2.color = Color(0.9569 * 255, 0.6549 * 255, 0.1686 * 255);
    dir2.scale = glm::vec3(0.3f);
    Transformable::UpdateLocals();
    dir2.position -= dir2.front * 3.f;

    point.color = Color(47, 194, 60);
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

    LampShader.SetVec3("u_Material.color", point.color.glCol3());

    while (!glfwWindowShouldClose(window))
    {
        DirectionLight::ShaderSet(shader);
        PointLight::ShaderSet(shader);
        SpotLight::ShaderSet(shader);

        glClearColor(camera.background.glCol4().r, camera.background.glCol4().g, camera.background.glCol4().b, camera.background.glCol4().a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rot += deltaTime;

        mover.Update(deltaTime);
        colChoiser.Update(deltaTime);
        flashlight.position = camera.position;
        flashlight.eulerAngles = camera.eulerAngles;
        
        Transformable::UpdateLocals();
        glBindVertexArray(VertexArrayObject);
        for (int i = 0; i < cubes.capacity(); i++)               // this cycle draws all cubes from  position and scales arrays
        {
            shader.use();
            shader.SetVec3("camPos", Camera::main->position);                                               // Set a view pos
            shader.SetMat4("u_Model", cubes[i].GetModelMat());                                              // Set Transformation matrix to shader
            shader.SetMat4("u_View", camera.GetView());                                              // Set View matrix to make a camera moving effect
            shader.SetMat4("u_Projection", camera.GetProjection());
            shader.use();
            glBindVertexArray(VertexArrayObject);
            glDrawArrays(GL_TRIANGLES, 0, 36);                                                    // Drawing all points as a trianges
        } 
        
        glBindVertexArray(LightVertexArrayObject);

        LampShader.SetVec3("u_Material.color", point.color.glCol3());
        LampShader.SetMat4("u_Model", point.GetModelMat());
        LampShader.SetMat4("u_View", Camera::main->GetView());
        LampShader.SetMat4("u_Projection", Camera::main->GetProjection());
        LampShader.use();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        LampShader.SetVec3("u_Material.color", dir.color.glCol3());
        LampShader.SetMat4("u_Model", dir.GetModelMat());
        LampShader.use();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        LampShader.SetVec3("u_Material.color", dir2.color.glCol3());
        LampShader.SetMat4("u_Model", dir2.GetModelMat());
        LampShader.use();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (buttPand > 0)
            buttPand -= deltaTime;

        if (glfwGetKey(window, GLFW_KEY_TAB) && buttPand <= 0)     // Switching a polygon mode
        {                                                               // 
            polygon = polygon ? false : true;                           //
            if (polygon)                                                //
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //
            else                                                        //
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);   //
            buttPand = 0.2f;                                            //
        }

        if (glfwGetKey(window, GLFW_KEY_1) && buttPand <= 0)    // Switching to Cat texture
        {
            shader.UseTexture = true;
            shader.DiffuseMap = CatTex;
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_2) && buttPand <= 0)    // Switching to Pug texture
        {                                                            //
            shader.UseTexture = true;
            shader.DiffuseMap = PugTex;                       //
            buttPand = 0.2f;                                         //
        }                                                            //

        if (glfwGetKey(window, GLFW_KEY_3) && buttPand <= 0){
            shader.UseTexture = true;
            shader.DiffuseMap = RockTex;
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_4) && buttPand <= 0){   // Switching to Monochrome mode
            shader.UseTexture = false;                              //
            shader.color = Color(116, 155, 63);     //
            buttPand = 0.2f;                                        //
        }                                                           //

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