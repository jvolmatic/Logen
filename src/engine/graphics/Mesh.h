#ifndef LOGEN_MESH_H
#define LOGEN_MESH_H
#include <string>

#include "Shader.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


namespace LogenCore::Graphics {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader &shader);

    public:
        const std::vector<Vertex> &GetVertices() { return this->vertices; }
        const std::vector<unsigned int> &GetIndices() { return this->indices; };
        const std::vector<Texture> &GetTextures() { return this->textures; };

    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

    private:
        void SetupMesh();
    };
}


#endif //LOGEN_MESH_H
