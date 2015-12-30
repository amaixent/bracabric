#pragma once
#include "Core/Objet3D.hpp"
#include "Liste/liste_Objet3D.hpp"
#include "glimac/glm.hpp"

using namespace glimac;

class Tas
{
private:
	int id;
	
	vec3 position;
	vec3 scaleTas;
	vec3 axeRotation;
	float angleRotation;
	
public:

	List ListObjet;
	Tas(int identifiant,List ListO,vec3 p,vec3 s,vec3 axeR,float angleR );
	Tas(int identifiant,string fichierObjet,vec3 p,vec3 s,vec3 axeR,float angleR);
	Tas();
	~Tas();

	List LoadObjectFromFile(string fichierObjet, List ListObjet);
	mat4 getModelMatrixTas(Objet3D obj);
	List getListObjet();

	void Draw(Shader shader);
	//void action();

};