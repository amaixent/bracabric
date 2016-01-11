#pragma once
#include "Core/Objet3D.hpp"
#include "Core/Tas_Action.hpp"
#include "glimac/glm.hpp"

using namespace glimac;

class Tas
{
private:
	int id;
	
	vec3 position;
	vec3 scaleTas;
	vec3 angleRotation;
	vector<Objet3D> listObjet;
	Objet3D objetBase;
	
public:

	
	Tas(int identifiant,vec3 p,vec3 s,vec3 angleR);
	Tas(int identifiant,string fichierObjet,vec3 p,vec3 s,vec3 angleR);
	Tas();
	~Tas();

	void LoadObjectFromFile(string fichierObjet);
	mat4 getModelMatrix();
	int getlistObjetSize();
	vec3 getPositionTas();
	int getIdTas();
	Objet3D getObjetBase();
	float getZ();

	void Draw(Shader shader,float ZCam);
	bool DrawCondition(int Zobj, float ZCam);
	void changeScene();
	//void action();

};