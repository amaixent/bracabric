#pragma once
#include <Model.hpp>


using namespace glm;

namespace glimac {

class Objet3D
{
private:
	int id;
	Model model;
	string emplacement;
	vec3 position;
	vec3 scaleObject;
	vec3 angleRotation;
	
public:
	
	Objet3D();
	Objet3D(int identifiant,Model mod,string path,vec3 p,vec3 s,vec3 angleR);
	Objet3D(string path);
	Objet3D(int identifiant, string path,vec3 p,vec3 s, vec3 angleR);
	Objet3D(int identifiant,vec3 p, vec3 s, vec3 angleR);
	Objet3D(const Objet3D &o);
	~Objet3D();

	void setPosition(vec3 newP);
	void setScale(vec3 newS);
	void setRotation(vec3 newR);

	vec3 getposition();
	vec3 getscaleObject();
	vec3 getangleRotation();
	string getEmplacement();
	int getId();
	

	mat4 getModelMatrix();
	void Draw(Shader shader);
	void changeScene();
	

	// void seDeplacer();
	// void action();

	/* data */
};
}