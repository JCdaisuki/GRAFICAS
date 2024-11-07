#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <glm/vec3.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <vector>
#include <string>
#include <GL/gl.h>

namespace PAG
{
    class Model
    {
        private:
            struct Vertex
            {
                glm::vec3 Position;
                glm::vec3 Normal;
            };

            // Datos de la malla
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            GLuint indexSP = 0;
            GLuint VAO;
            GLuint VBO;
            GLuint IBO;

            // Configura los buffers de la malla
            void setupMesh();

            // Carga el modelo desde un archivo utilizando Assimp
            void loadModel(std::string path);

            // Procesa un nodo del árbol de Assimp y carga la primera malla encontrada
            void processNode(aiNode *node, const aiScene *scene);

            // Procesa una malla de Assimp y llena los datos de vértices e índices
            void processMesh(aiMesh *mesh);

        public:
            Model(char *path);

            // Dibuja el modelo
            void Draw();

            void setIndexSP ( GLuint idx ){ indexSP = idx; };
            GLuint getIndexSP (){ return indexSP; };
            GLuint getIdVAO () { return VAO;};
            GLuint getNumIndices () { return indices.size();};

            ~Model();
    };
}

#endif // MODEL_H