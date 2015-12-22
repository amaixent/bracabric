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
	
public:
	
	Objet3D();
	Objet3D(int identifiant,Model mod,string path,vec3 p,vec3 s);
	Objet3D(string path);
	Objet3D(int identifiant, string path,vec3 p,vec3 s);
	Objet3D(const Objet3D &o);
	~Objet3D();

	void setPosition(vec3 newp);
	void setScale(vec3 news);
	

	mat4 getModelMatrix();
	void Draw(Shader shader);
	

	// void seDeplacer();
	// void action();

	/* data */
};
}