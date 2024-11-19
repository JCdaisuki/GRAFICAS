cmake_minimum_required(VERSION 3.29)
project(GRAFICAS)

set(CMAKE_CXX_STANDARD 20)

file(GLOB IMGUI imgui/*cpp)

add_executable(GRAFICAS glad/src/glad.c ${IMGUI}
        main.cpp
        Renderer.cpp
        Renderer.h
        GUI.cpp
        GUI.h
        ShaderProgram.cpp
        ShaderProgram.h
        ShaderObject.cpp
        ShaderObject.h
        Camera.cpp
        Camera.h
        Model.cpp
        Model.h
        Material.cpp
        Material.h
)

target_include_directories(GRAFICAS PUBLIC glad/include)

find_package(glfw3)
target_link_libraries(GRAFICAS glfw "-static")

find_package(glm)
target_link_libraries(GRAFICAS glm::glm "-static")

find_package(assimp)
target_link_libraries(GRAFICAS assimp::assimp "-static")