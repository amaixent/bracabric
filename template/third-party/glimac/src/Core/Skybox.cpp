#include <Core/Skybox.hpp>

using namespace glimac;
	
	Skybox::Skybox(){}
	
	Skybox::~Skybox(){

	}

void Skybox::loadSkybox(int identifiant,string fichierSkybox){

  	// if (identifiant == 3)
   //  {
   //         skyboxShader.loadShader("projet/shaders/skybox_lampe_torche.vs.glsl", "projet/shaders/skybox_lampe_torche.fs.glsl");

   //  }
   //  else{
           skyboxShader.loadShader("projet/shaders/skybox.vs.glsl", "projet/shaders/skybox.fs.glsl");

    // }
 
	GLfloat skyboxVertices[] = {
    // Positions          
    -40.0f,  40.0f, -40.0f,
    -40.0f, -40.0f, -40.0f,
     40.0f, -40.0f, -40.0f,
     40.0f, -40.0f, -40.0f,
     40.0f,  40.0f, -40.0f,
    -40.0f,  40.0f, -40.0f,

    -40.0f, -40.0f,  40.0f,
    -40.0f, -40.0f, -40.0f,
    -40.0f,  40.0f, -40.0f,
    -40.0f,  40.0f, -40.0f,
    -40.0f,  40.0f,  40.0f,
    -40.0f, -40.0f,  40.0f,

     40.0f, -40.0f, -40.0f,
     40.0f, -40.0f,  40.0f,
     40.0f,  40.0f,  40.0f,
     40.0f,  40.0f,  40.0f,
     40.0f,  40.0f, -40.0f,
     40.0f, -40.0f, -40.0f,

    -40.0f, -40.0f,  40.0f,
    -40.0f,  40.0f,  40.0f,
     40.0f,  40.0f,  40.0f,
     40.0f,  40.0f,  40.0f,
     40.0f, -40.0f,  40.0f,
    -40.0f, -40.0f,  40.0f,

    -40.0f,  40.0f, -40.0f,
     40.0f,  40.0f, -40.0f,
     40.0f,  40.0f,  40.0f,
     40.0f,  40.0f,  40.0f,
    -40.0f,  40.0f,  40.0f,
    -40.0f,  40.0f, -40.0f,

    -40.0f, -40.0f, -40.0f,
    -40.0f, -40.0f,  40.0f,
     40.0f, -40.0f, -40.0f,
     40.0f, -40.0f, -40.0f,
    -40.0f, -40.0f,  40.0f,
     40.0f, -40.0f,  40.0f
	};
		
	vector<const string> faces;
	string path;
	path = fichierSkybox + "right.tga";
	faces.push_back(path);
	path = fichierSkybox + "left.tga";
	faces.push_back(path);
	path = fichierSkybox + "up.tga";
	faces.push_back(path);
	path = fichierSkybox + "bottom.tga";
	faces.push_back(path);
	path = fichierSkybox + "back.tga";
	faces.push_back(path);
	path = fichierSkybox + "front.tga";
	faces.push_back(path);
	skyboxTexture = loadCubemap(faces); 

	
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);


	}

GLuint Skybox::loadCubemap(vector<const string> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);

    std::unique_ptr<Image> image;
	
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = loadImage(faces[i]);
 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGBA,image->getWidth(),image->getHeight(),0,GL_RGBA,GL_FLOAT,image->getPixels());
      
      
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
} 
void Skybox::Draw(TrackballCamera camera,float screenWidth, float screenHeight, int idScene){

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
  // Draw skybox first

  
  
  glDepthMask(GL_FALSE);// Remember to turn depth writing off
  glm::mat4 view = camera.getViewMatrix();
  skyboxShader.Use();

  //Mouvement de la skybox
  view = glm::translate(view, glm::vec3(0,0,-30));

  glUniformMatrix4fv(glGetUniformLocation(this->skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(this->skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  // skybox cube
  glBindVertexArray(skyboxVAO);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthMask(GL_TRUE);
}

void Skybox::changeSkybox(){
	glDeleteBuffers(1, &skyboxVBO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteTextures( 1,&skyboxTexture);
}
