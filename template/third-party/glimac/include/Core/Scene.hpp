#pragma once
#include "Core/Objet3D.hpp"
#include "Shader.hpp"
#include "Liste/liste_Objet3D.hpp"
#include <Core/Trajectoire.hpp>
#include <Camera/FreeflyCamera.hpp>

namespace glimac {

class Scene
{
private:
	int id;
	// int nbObjet; //la variable n'est plus utile si on utilise une liste
	Shader shader;
	List ListObjet; //pardon...mais j'en pouvais plus du tableau c'est plus simple une liste dans ce cas.
	int idTrajectoire;
	
public:

	Scene(string fichierVs,string fichierFs,string fichierObjet);
	~Scene();

	List Load2ObjetsTmp(List ListObjet);
	List LoadObjectFromFile(string fichierObjet, List ListObjet); //On peut s'aider de la fonction Load2objettmp() pour utiliser les listes pour charger les objets.
	void Draw(Trajectoire trajcam, FreeflyCamera camera, GLuint screenWidth, GLuint screenHeight);

	/* data */
};
}