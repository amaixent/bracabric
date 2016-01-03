#include "Core/Objet3D.hpp"

namespace glimac {

	Objet3D::Objet3D(){

	}
	Objet3D::Objet3D(int identifiant, Model mod, string path, vec3 p, vec3 s, vec3 angleR){
		id = identifiant;
		model = mod;
		emplacement = path;
		position = p;
		scaleObject = s;
		angleRotation = angleR;
	}
	Objet3D::Objet3D(string path){
		emplacement = path;
		model.loadModel(emplacement);
		position = glm::vec3(0.0f, -1.75f, -3.0f);
		scaleObject = glm::vec3(0.2f, 0.2f, 0.2f);
		angleRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	
	}
	
	Objet3D::Objet3D(int identifiant, string path, vec3 p, vec3 s, vec3 angleR){
		id = identifiant;
		emplacement = path;
		model.loadModel(emplacement);
		position = p;
		scaleObject = s;
		angleRotation = angleR;
		
	}
	Objet3D::Objet3D(int identifiant,vec3 p, vec3 s, vec3 angleR){
		id = identifiant;
		position = p;
		scaleObject = s;
		angleRotation = angleR;
		
	}

	Objet3D::Objet3D(const Objet3D &o){
		id = o.id;
		model = o.model;
		emplacement = o.emplacement;
		position = o.position;
		scaleObject = o.scaleObject;
		angleRotation = o.angleRotation;

	}
	Objet3D::~Objet3D(){

	}

	void Objet3D::setPosition(vec3 newP){
		position = newP;

	}
	void Objet3D::setScale(vec3 newS){
		scaleObject = newS;

	}
	void Objet3D::setRotation(vec3 newR){
		angleRotation = newR;

	}

	vec3 Objet3D::getposition(){
		return position;
	}
	vec3 Objet3D::getscaleObject(){
		return scaleObject;
	}
	vec3 Objet3D::getangleRotation(){
		return angleRotation;
	}


	
	mat4 Objet3D::getModelMatrix(){
		mat4 modelMatrix  = mat4(1.0f);
        modelMatrix = translate(modelMatrix, position); 
        modelMatrix = scale(modelMatrix, scaleObject);
		modelMatrix = rotate(modelMatrix, radians(angleRotation[0]), vec3(1,0,0));
        modelMatrix = rotate(modelMatrix, radians(angleRotation[1]), vec3(0,1,0));
        modelMatrix = rotate(modelMatrix, radians(angleRotation[2]), vec3(0,0,1));



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