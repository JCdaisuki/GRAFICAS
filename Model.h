#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <GL/gl.h>

#include <vector>
#include <string>

namespace PAG
{
    class Model
    {
        public:
            enum class ModoVisualizacion
            {
                ModoAlambre,
                ModoPlano
            };

        private:
            struct Vertex
            {
                glm::vec3 Position;
                glm::vec3 Normal;
            };

            std::string nombreModelo;

            // Datos de la malla
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            GLuint indexSP = 0;
            GLuint VAO;
            GLuint VBO;
            GLuint IBO;

            ModoVisualizacion modoVisualizacion = ModoVisualizacion::ModoPlano;

            // Configura los buffers de la malla
            void setupMesh();

            // Carga el modelo desde un archivo utilizando Assimp
            void loadModel(std::string path);

            // Procesa un nodo del árbol de Assimp y carga la primera malla encontrada
            void processNode(aiNode *node, const aiScene *scene);

            // Procesa una malla de Assimp y llena los datos de vértices e índices
            void processMesh(aiMesh *mesh);

        public:
            Model(char *path, std::string modelo);

            // Dibuja el modelo
            void Draw();

            void SetIndexSP ( GLuint idx ){ indexSP = idx; };
            void SetModoVisualizacion(ModoVisualizacion modo){ modoVisualizacion = modo; };
            std::string GetNombreModelo(){ return nombreModelo; };
            GLuint GetIndexSP (){ return indexSP; };
            GLuint GetIdVAO () { return VAO;};
            GLuint GetNumIndices () { return indices.size();};
            GLenum GetPolygonMode();

            ~Model();
    };
}

#endif // MODEL_H