#include "Core/Objet3D.hpp"

namespace glimac {

	Objet3D::Objet3D(){

	}
	Objet3D::Objet3D(int identifiant,Model mod,string path,vec3 p,vec3 s){
		id = identifiant;
		model = mod;
		emplacement = path;
		position = p;
		scaleObject = s;
	}
	Objet3D::Objet3D(string path){
		emplacement = path;
		model.loadModel(emplacement);
		position = glm::vec3(0.0f, -1.75f, -3.0f);
		scaleObject = glm::vec3(0.2f, 0.2f, 0.2f);
	}
	
	Objet3D::Objet3D(int identifiant, string path,vec3 p,vec3 s){
		id = identifiant;
		emplacement = path;
		model.loadModel(emplacement);
		position = p;
		scaleObject = s;
	}

	Objet3D::Objet3D(const Objet3D &o){
		id = o.id;
		model = o.model;
		emplacement = o.emplacement;
		position = o.position;
		scaleObject = o.scaleObject;
	}
	Objet3D::~Objet3D(){

	}

	void Objet3D::setPosition(vec3 newp){
		position = newp;

	}
	void Objet3D::setScale(vec3 news){
		scaleObject = news;

	}

	
	mat4 Objet3D::getModelMatrix(){
		mat4 modelMatrix  =mat4(1.0f);
        modelMatrix = translate(modelMatrix, position); // Translate it down a bit so it's at the center of the scene
        modelMatrix = scale(modelMatrix, scaleObject);

        return modelMatrix;
	}

	void Objet3D::Draw(Shader shader){
		model.Draw(shader);
	}

	// void Objet3D::seDeplacer(){

	// }

	// void Objet3D::action(){

	// }
}