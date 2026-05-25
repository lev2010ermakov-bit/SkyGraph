cmake_minimum_required(VERSION 3.10)
project(OpenGL-Render)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

message("cloning custom version of assimp...")
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/lev2010ermakov-bit/assimp.git
    GIT_TAG v5.4.3-fixed
)

FetchContent_MakeAvailable(assimp)

find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE_FILE 
    "main.cpp"
    "SkyGraph/src/*.cpp"
    "SkyGraph/third-party/glad/src/glad.c"
    "SkyGraph/third-party/stb/src/stb_image.c"

    "Scripts/*.cpp"
)

add_executable(build ${SOURCE_FILE})

target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkyGraph/third-party/glad/include/)
target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkyGraph/third-party/stb/include/)
target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkyGraph/third-party/assimp/include/)
target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkyGraph/include/)
target_link_libraries(build PRIVATE glfw OpenGL::OpenGL glm::glm dl assimp)