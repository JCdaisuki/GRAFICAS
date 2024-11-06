cmake_minimum_required(VERSION 3.29)
project(GRAFICAS)

set(CMAKE_CXX_STANDARD 20)

file(GLOB IMGUI imgui/*cpp)

add_executable(GRAFICAS main.cpp Renderer.cpp Renderer.h ${IMGUI}
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
)

find_package(glad)
target_link_libraries(GRAFICAS glad::glad "-static")

find_package(glfw3)
target_link_libraries(GRAFICAS glfw "-static")

find_package(glm)
target_link_libraries(GRAFICAS glm::glm "-static")

find_package(assimp)
target_link_libraries(GRAFICAS assimp::assimp "-static")