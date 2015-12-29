#pragma once
#include "Core/Objet3D.hpp"
#include "Shader.hpp"
#include "Liste/liste_Objet3D.hpp"
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
	List ListObjet; 
	int idTrajectoire;
	
public:

	Scene(string fichierVs,string fichierFs,string fichierObjet);
	~Scene();

	List Load2ObjetsTmp(List ListObjet);
	List LoadObjectFromFile(string fichierObjet, List ListObjet);
	void Draw(Trajectoire trajcam, TrackballCamera camera, GLuint screenWidth, GLuint screenHeight);

	/* data */
};
}