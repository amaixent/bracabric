#include <string>
#include <assimp/scene.h>

using namespace std;

struct Texture {

    GLuint id;
    string type;
    aiString path;  // We store the path of the texture to compare with other textures
};