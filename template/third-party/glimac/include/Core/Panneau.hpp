#pragma once

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Camera/FreeflyCamera.hpp>
#include <Camera/TrackballCamera.hpp>
#include "Shader.hpp"

namespace glimac {

class Panneau
{
private:
	int width, height;
	Shader panneauShader;
    GLuint panneauTexture;
    GLuint panneauVAO, panneauVBO, panneauEBO;
    GLuint loadTexture(string cheminTexture);

	
public:
	Panneau();
	~Panneau();

	void loadPanneau(string cheminTexture);
	void fermeturePanneau();
	void Draw(TrackballCamera camera, GLuint screenWidth, GLuint screenHeight);

	};
}