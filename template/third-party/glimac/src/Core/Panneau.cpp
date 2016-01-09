#include <Core/Panneau.hpp>

using namespace glimac;

Panneau::Panneau(){
    panneauShader.loadShader("projet/shaders/3D.vs.glsl","projet/shaders/tex3D.fs.glsl");

}
Panneau::~Panneau(){

}

void Panneau::loadPanneau(string cheminTexture){


    panneauShader.loadShader("projet/shaders/skybox_lampe_torche.vs.glsl", "projet/shaders/skybox_lampe_torche.fs.glsl");
 
	GLfloat panneauVertices[] ={
		-0.5f, -0.5f, 0.5f, 
		-0.5f, 0.0f, 0.5f,
		0.5f, 0.5f, 0.5f, 
		0.5f, 0.0f, -0.5f
	};

	panneauTexture = loadTexture(cheminTexture); 

	
    glGenVertexArrays(1, &panneauVAO);
    glGenBuffers(1, &panneauVBO);
    glBindVertexArray(panneauVAO);
    glBindBuffer(GL_ARRAY_BUFFER, panneauVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(panneauVertices), &panneauVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
}
GLuint Panneau::loadTexture(string cheminTexture)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);

    std::unique_ptr<Image> image;

    image = loadImage(cheminTexture);

    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexImage2D( GL_TEXTURE_2D,0,GL_RGBA,image->getWidth(),image->getHeight(),
        0,GL_RGBA,GL_FLOAT,image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    return textureID;
} 

void Panneau::fermeturePanneau(){
    glDeleteBuffers(1, &panneauVBO);
    glDeleteVertexArrays(1, &panneauVAO);
    glDeleteTextures( 1,&panneauTexture);
}
void Panneau::Draw( TrackballCamera camera, GLuint screenWidth, GLuint screenHeight){
  
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
  glm::mat4 view = camera.getViewMatrix();
  panneauShader.Use();
  glUniformMatrix4fv(glGetUniformLocation(this->panneauShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(this->panneauShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  
  glBindVertexArray(panneauVAO);
  glBindTexture(GL_TEXTURE_2D, panneauTexture);
  glDrawArrays(GL_QUADS, 0, 1);
  glBindVertexArray(0);
}
