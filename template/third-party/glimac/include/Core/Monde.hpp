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
	Panneau panneauDebut;

	
public:
	TrackballCamera trackCam;
	Monde();
	~Monde();

	int getSceneId();
	void chargeScene(int identifiant);
	void Draw( GLuint screenWidth, GLuint screenHeight);
	};
}