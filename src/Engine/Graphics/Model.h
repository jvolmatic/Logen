#ifndef LOGEN_MODEL_H
#define LOGEN_MODEL_H
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "assimp/scene.h"

namespace LogenCore::Graphics {
    class Model {
    public:
        Model(const char *path) {
            this->LoadModel(path);
        }

        void Draw(Shader &shader);

    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;

        void LoadModel(std::string path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };
}


#endif //LOGEN_MODEL_H
