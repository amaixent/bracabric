#pragma once

// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glimac/Image.hpp>
#include <Mesh/Mesh.hpp>




class Model 
{
    public:
        /*  Functions   */
        Model()
        {
        }
        Model(string path)
        {
            this->loadModel(path);
        }
        void loadModel(string path);
        void Draw(Shader shader);	
    private:
        /*  Model Data  */
        vector<Mesh> meshes;
        string directory;
        vector<Texture> textures_loaded;
        /*  Functions   */
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        GLint TextureFromFile(const char* path, string directory);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, 
                                             string typeName);
};