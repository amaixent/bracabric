
#pragma once

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Core/Trajectoire.hpp>
#include <Camera/FreeflyCamera.hpp>
#include <Camera/TrackballCamera.hpp>
#include "Shader.hpp"


using namespace glimac;

class Skybox
{
private:
    Shader skyboxShader;
    GLuint skyboxTexture;
    GLuint skyboxVAO, skyboxVBO;
    GLuint loadCubemap(vector<const string> faces);
    
public:
	Skybox();
    ~Skybox();

    void loadSkybox(int identifiant, string fichierSkybox);
    void Draw(TrackballCamera camera,float screenWidth, float screenHeight);
    void changeSkybox();
};



