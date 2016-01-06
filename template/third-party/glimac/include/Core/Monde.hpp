#pragma once

#include "Core/Scene.hpp"
#include "Core/Skybox.hpp"
namespace glimac {

class Monde
{
private:
	int nbScenes;
	Scene myScene;
	Skybox mySkybox;

	
public:
	Monde();
	~Monde();

	void chargeScene(int identifiant);
	void Draw(Trajectoire trajcam, TrackballCamera camera, GLuint screenWidth, GLuint screenHeight);
	/* data */
	};
}