#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include "scripts/Loader/Loader.hpp"
#include "scripts/CameraMover/CameraMover.hpp"

#include <SkyGraph.hpp>

bool colorDebug;
int currentColDebug;
int currentColItem;

sky::Shader LitShader;
sky::Shader UnlitShader;

sky::UnlitMat PointMat;
sky::UnlitMat DirMat;
sky::UnlitMat Dir2Mat;

sky::LitMat LightMat;

sky::DirectionLight dir;
sky::DirectionLight dir2;
sky::PointLight point;
sky::SpotLight flashlight;
bool flashlightTurn = true;

sky::Camera camera;

CameraMover mover;

int main(int agrc, char *agrv[])
{
    sky::InitWindow("my window", 800, 600);

    camera = sky::Camera(75, 0.1f, 10000.f);
    sky::Camera::SetMain(camera);
    camera.position = glm::vec3(-3.31473, -1.567f, 6.05006f);
    camera.eulerAngles = glm::vec3(14.9043f, -61.7206f, 0.0f);
    camera.background = sky::Color(45, 138, 189);    //beauty blue color
    //camera.background = Color(209, 46, 33);    //beauty red color
    //camera.background = Color(20);

    curr_agrv = agrv[0];
    

    mover = CameraMover();  // Create a class that moves the camera
    mover.camera = &camera;

    sky::Model cube(GetFullPath("assets/models/cube/cube.obj"));

    bool polygon;
    float buttPand;

    sky::Texture2D PugTex(GetFullPath("assets/textures/PugImage.png").c_str(), GL_RGBA, GL_LINEAR);         // Loading a Textures
    sky::Texture2D CatSpec(GetFullPath("assets/textures/catSpecular.png").c_str(), GL_RGBA, GL_LINEAR);     //
    sky::Texture2D EmissionMap(GetFullPath("assets/textures/EmissionMap.jpg").c_str(), GL_RGB, GL_LINEAR);  //
    sky::Texture2D CatTex(GetFullPath("assets/textures/catImage.jpg").c_str(), GL_RGB, GL_LINEAR);          //
    sky::Texture2D RockTex(GetFullPath("assets/textures/rockImage.jpg").c_str(), GL_RGB, GL_LINEAR);        // 
    sky::Texture2D CarTex(GetFullPath("assets/models/tiny-lowpoly-car/car-texture.png").c_str(), GL_RGBA, GL_NEAREST);

    LitShader.Setup(GetFullPath("assets/shaders/Lit/VertShader.glsl").c_str(),
                 GetFullPath("assets/shaders/Lit/FragShader.glsl").c_str());
    UnlitShader.Setup(GetFullPath("assets/shaders/Unlit/UnlitVertShader.glsl").c_str(), 
                     GetFullPath("assets/shaders/Unlit/UnlitFragShader.glsl").c_str());

    sky::Transformable carTransformable;
    carTransformable.eulerAngles = glm::vec3(-180, 180, 0);
    sky::Model carModel(GetFullPath("assets/models/tiny-lowpoly-car/car.obj"));

    LightMat.SetShader(LitShader);
    LightMat.color = sky::Color(255);

    PointMat.SetShader(UnlitShader);

    DirMat.SetShader(UnlitShader);
    Dir2Mat.SetShader(UnlitShader);

    LightMat.Shiness = 256.f;
    LightMat.Roughness = 1.f;
    LightMat.ShadowColor = sky::Color(50);
    LightMat.DiffuseMap = &CarTex;

    dir.color = sky::Color(255.0f);
    dir.eulerAngles.y = 90.f;
    dir.eulerAngles.x = 20;
    dir.scale = glm::vec3(0.3f);
    dir.position -= dir.getLocals().front * 3.f;

    dir2.eulerAngles.y = -90;
    dir2.eulerAngles.x = 20;
    dir2.color = sky::Color(0.9569 * 255, 0.6549 * 255, 0.1686 * 255);
    dir2.scale = glm::vec3(0.3f);
    dir2.position -= dir2.getLocals().front * 3.f;

    point.color = sky::Color(40, 200, 255);
    point.position = glm::vec3(7);
    point.constant = 1.0f;
    point.linear = 0.09f;
    point.quadratic = 0.032f;

    point.position = glm::vec3(0.0f);
    point.scale = glm::vec3(0.1f);

    flashlight.color = sky::Color(255);
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

    sky::Transformable child, parent;
    child.scale = glm::vec3(0.5f);
    parent.scale = glm::vec3(0.4f);
    child.SetParent(parent);    
    parent.position.x = 8;
    child.position.y = 2;

    while (!sky::WindowShouldClose())
    {
        sky::Time::Update();
        dir.BindToShader(LitShader, 0);
        point.BindToShader(LitShader, 0);
        flashlight.BindToShader(LitShader, 0);

        sky::ClearWindow(sky::Camera::main->background);
        mover.Update();
        
        flashlight.position = camera.position;
        flashlight.eulerAngles = camera.eulerAngles;

        LightMat.Bind();
        LitShader.SetVec3("camPos", sky::Camera::main->position);                                               // Set a view pos
        LitShader.SetMat4("u_Model", carTransformable.GetModelMat());                                              // Set Transformation matrix to shader
        LitShader.SetMat4("u_View", sky::Camera::main->GetView());                                              // Set View matrix to make a camera moving effect
        LitShader.SetMat4("u_Projection", sky::Camera::main->GetProjection());
        carModel.Draw(LightMat);

        PointMat.Bind();
        UnlitShader.SetMat4("u_Model", point.GetModelMat());
        UnlitShader.SetMat4("u_View", sky::Camera::main->GetView());
        UnlitShader.SetMat4("u_Projection", sky::Camera::main->GetProjection());
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

        sky::ShowWindow();

        if (buttPand > 0)
            buttPand -= sky::Time::deltaTime;

        if (sky::Input::GetKey(sky::keycode::TAB) && buttPand <= 0)     // Switching a polygon mode
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
        if (sky::Input::GetKey(sky::keycode::F) && buttPand <= 0){
            if (flashlightTurn){
                flashlight.color = sky::Color(0);
            }
            else{
                flashlight.color = sky::Color(255);
            }
            flashlightTurn = !flashlightTurn;
            buttPand = 0.2f;
        }

        if (sky::Input::GetKey(sky::keycode::L) && buttPand <= 0){
            std::cout << "pos: " << camera.position.x << " " << camera.position.y << " " << camera.position.z << std::endl;
            std::cout << "rot: " << camera.eulerAngles.x << " " << camera.eulerAngles.y << " " << camera.eulerAngles.z << std::endl;
            buttPand = 0.2f;
        }                         //
    }
    return 0;
}