#pragma once

#include <GL/glew.h>
#include <vector>
#include <sstream>
#include <string>

#include <Mesh/Vertex.hpp>
#include <Mesh/Texture.hpp>
#include "Shader.hpp"


class Mesh {
    public:
        /*  Mesh Data  */
        vector<Vertex> vertices;
        vector<GLuint> indices;
        vector<Texture> textures;
        /*  Functions  */
        Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
        void Draw(Shader shader);
    private:
        /*  Render data  */
        GLuint VAO, VBO, EBO;
        /*  Functions    */
        void setupMesh();
}; 