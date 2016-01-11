#pragma once
#include <GL/glew.h>
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
	int pause;
	GLuint screenWidth,screenHeight;

	
public:
	Panneau panneauLoading;
	TrackballCamera trackCam;
	Monde(GLuint width,GLuint height,SDLWindowManager &windowManager);
	~Monde();

	int getSceneId();
	void chargeScene(int identifiant,SDLWindowManager &windowManager);
	void Draw();
	void changePause();
	void loading(SDLWindowManager &windowManager);
	bool enPause();
};
}