#pragma once

#include "Core/Scene.hpp"
#include "Core/Skybox.hpp"
#include "Core/Panneau.hpp"
namespace glimac {

class Monde
{
private:
	int nbScenes;
	Scene myScene;
	Skybox mySkybox;
	Panneau panneauDebut,panneauLoading;
	int pause;
	GLuint screenWidth,screenHeight;

	
public:
	TrackballCamera trackCam;
	Monde(GLuint width,GLuint height);
	~Monde();

	int getSceneId();
	void chargeScene(int identifiant);
	void Draw();
	void changePause();
	};
}