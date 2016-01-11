#pragma once
#include "Core/Tas.hpp"
#include "Shader.hpp"
#include "Core/Panneau.hpp"
#include <Core/Skybox.hpp>
#include <Camera/TrackballCamera.hpp>

#include "glimac/glm.hpp"

namespace glimac {

class Scene
{
private:
	int id;
	Shader shader;
	vector<Tas> tabTas; 
	int idTrajectoire;
	Skybox mySkybox;
	
	
public:
	Panneau panneauFin;
	Scene();
	//Scene(int identifiant, string fichierVs,string fichierFs,string fichierTas,string fichierPanneauFin);
	~Scene();

	//List LoadObjectFromFile(string fichierObjet, List ListObjet);
	int getId();
	void changeScene();
	void chargeScene(int identifiant, string fichierVs,string fichierFs,string fichierTas,string fichierPanneauFin);
	void LoadTasFromFile(string fichierTas);
	void Draw(TrackballCamera camera, GLuint screenWidth, GLuint screenHeight,float ZCam);

	/* data */
};
}