#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "imgui/imgui_impl_opengl3_loader.h"
#include <glad/glad.h>

namespace PAG
{
    class ShaderProgram;

    class Model
    {
        struct Vertex {
            glm::vec3 Position;
            glm::vec3 Normal;
            glm::vec2 TexCoords;
        };

        private:

            class Mesh
            {
                public:
                    // mesh data
                    std::vector<Vertex>       vertices;
                    std::vector<unsigned int> indices;

                    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
                    void Draw(ShaderProgram &shader);
                private:
                    //  render data
                    unsigned int VAO, VBO, EBO;

                    void setupMesh();
            };

            // model data
            std::vector<Mesh> meshes;
            std::string directory;

            void loadModel(std::string path);
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        public:
            Model(char *path)
            {
                loadModel(path);
            }
            void Draw(ShaderProgram &shader);
    };

}

#endif //MODEL_H
