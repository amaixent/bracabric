#pragma once
#include "Core/Objet3D.hpp"
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
	vector<Objet3D> listObjet;
	Objet3D objetBase;
	
public:

	
	Tas(int identifiant,vec3 p,vec3 s,vec3 axeR,float angleR );
	Tas(int identifiant,string fichierObjet,vec3 p,vec3 s,vec3 axeR,float angleR);
	Tas();
	~Tas();

	void LoadObjectFromFile(string fichierObjet);
	mat4 getModelMatrix();
	int getlistObjetSize();

	void Draw(Shader shader);
	//void action();

};