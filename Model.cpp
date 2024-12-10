
#include <fstream>
#include <iostream>
#include <sstream>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "Camera.h"
#include "Model.h"

#include "lodepng.h"

namespace PAG
{
    Model::Model(char *path, std::string modelo)
    {
        loadModel(path);
        setupMesh();

        nombreModelo = modelo;
    }

    void Model::Draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Model::setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                     &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        glBindVertexArray(0);
    }

    void Model::loadModel(std::string path)
    {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            throw std::runtime_error("ERROR::ASSIMP::" + std::string(import.GetErrorString()));
        }

        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh);
        }

        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    void Model::processMesh(aiMesh *mesh)
    {
        vertices.clear();
        indices.clear();

        for(int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;

            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;

            vertices.push_back(vertex);
        }

        for(int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }
    }

    GLenum Model::GetPolygonMode()
    {
        if(modoVisualizacion == ModoVisualizacion::ModoAlambre)
        {
            return GL_LINE;
        }

        if(modoVisualizacion == ModoVisualizacion::ModoPlano)
        {
            return GL_FILL;
        }
    }

    void Model::Translate(glm::vec3 translation)
    {
        modelMatrix = glm::translate(modelMatrix, translation);
    }

    void Model::Rotate(float angle, glm::vec3 axis)
    {
        //Calculamos el centro del modelo como la media de los vértices
        glm::vec3 centro(0.0f);

        if (!vertices.empty())
        {
            for (const auto& vertex : vertices)
            {
                centro += vertex.Position;
            }
            centro /= static_cast<float>(vertices.size());
        }

        //Movemos el modelo al origen de coordenadas, lo rotamos y lo devolvemos a su posición original
        modelMatrix = glm::translate(modelMatrix, -centro);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
        modelMatrix = glm::translate(modelMatrix, centro);
    }

    void Model::Scale(glm::vec3 scale)
    {
        modelMatrix = glm::scale(modelMatrix, scale);
    }

    void Model::CargarTextura(std::string rutaTextura)
    {
        /** Carga un png de disco https://lodev.org/lodepng */
        std::vector<unsigned char> imagen; // Los píxeles de la imagen
        unsigned ancho, alto;
        unsigned error = lodepng::decode (imagen, ancho, alto, rutaTextura);

        if (error)
        {
            std::string mensaje = rutaTextura + " no se pudo cargar";
            throw std::runtime_error ( mensaje );
        }

        // La textura se carga del revés, así que vamos a darle la vuelta
        unsigned char *imgPtr = &imagen[0];
        int numeroDeComponentesDeColor = 4;
        int incrementoAncho = ancho * numeroDeComponentesDeColor; // Ancho en bytes

        unsigned char* top = nullptr;
        unsigned char* bot = nullptr;
        unsigned char temp = 0;

        for (int i = 0; i < alto / 2; i++)
        {
            top = imgPtr + i * incrementoAncho;
            bot = imgPtr + (alto - i - 1) * incrementoAncho;

            for (int j = 0; j < incrementoAncho; j++)
            {
                temp = *top;
                *top = *bot;
                *bot = temp;
                ++top;
                ++bot;
            }
        }

        glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagen.data() );
    }

    Model::~Model()
    {
        if (VBO != 0)
        {
            glDeleteBuffers(1, &VBO);
        }

        if (VAO != 0)
        {
            glDeleteVertexArrays(1, &VAO);
        }

        if (IBO != 0)
        {
            glDeleteBuffers(1, &IBO);
        }
    }
}