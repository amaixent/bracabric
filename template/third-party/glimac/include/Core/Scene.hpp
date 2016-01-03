#pragma once
#include "Core/Tas.hpp"
#include "Shader.hpp"
#include <Core/Trajectoire.hpp>
#include <Camera/FreeflyCamera.hpp>
#include <Camera/TrackballCamera.hpp>
#include "glimac/glm.hpp"

namespace glimac {

class Scene
{
private:
	int id;
	Shader shader;
	//List ListObjet;
	Tas tabTas[6]; 
	int idTrajectoire;
	
public:

	Scene(int identifiant, string fichierVs,string fichierFs,string fichierTas);
	~Scene();

	//List LoadObjectFromFile(string fichierObjet, List ListObjet);
	void LoadTasFromFile(string fichierTas);
	void Draw(Trajectoire trajcam, TrackballCamera camera, GLuint screenWidth, GLuint screenHeight);

	/* data */
};
}