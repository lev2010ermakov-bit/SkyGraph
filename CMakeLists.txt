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

file(GLOB_RECURSE SKYGRAPH_SOURCE
    "src/*.cpp"
    "third-party/glad/src/glad.c"
    "third-party/stb/src/stb_image.c"
)

file(GLOB_RECURSE MAIN_SOURCE
    "main.cpp"
    "scripts/*.cpp"
)

add_library(SkyGraph STATIC)
target_sources(SkyGraph PRIVATE ${SKYGRAPH_SOURCE})

add_executable(build ${MAIN_SOURCE})

target_include_directories(SkyGraph
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glad/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/stb/include/
    PUBLIC  
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_include_directories(build 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glad/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/stb/include/
)

target_link_libraries(SkyGraph PRIVATE glfw OpenGL::OpenGL glm::glm dl assimp)
target_link_libraries(build PRIVATE glfw OpenGL::OpenGL glm::glm dl SkyGraph assimp)