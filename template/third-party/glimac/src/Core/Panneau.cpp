#include <Core/Panneau.hpp>

using namespace glimac;

Panneau::Panneau(){
}
Panneau::~Panneau(){

}

void Panneau::loadPanneau(string cheminTexture){

    panneauShader.loadShader("projet/shaders/3D.vs.glsl", "projet/shaders/tex3D.fs.glsl");


    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    
    glGenVertexArrays(1, &panneauVAO);
    glGenBuffers(1, &panneauVBO);
    glGenBuffers(1, &panneauEBO);

    glBindVertexArray(panneauVAO);

    glBindBuffer(GL_ARRAY_BUFFER, panneauVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,panneauEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    panneauTexture = loadTexture(cheminTexture);

}
GLuint Panneau::loadTexture(string cheminTexture)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::unique_ptr<Image> image;
    image = loadImage(cheminTexture);
    
     glTexImage2D( GL_TEXTURE_2D,0,GL_RGBA,image->getWidth(),image->getHeight(),
        0,GL_RGBA,GL_FLOAT,image->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    return texture;
} 


void Panneau::Draw( TrackballCamera camera, GLuint screenWidth, GLuint screenHeight){
  
        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, panneauTexture);

        // Activate shader
        panneauShader.Use();       
        
        // Draw container
        glBindVertexArray(panneauVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

}

void Panneau::fermeturePanneau(){
    glDeleteBuffers(1, &panneauVBO);
    glDeleteVertexArrays(1, &panneauVAO);
    glDeleteTextures( 1,&panneauTexture);
}
