#include "Core/Objet3D.hpp"

namespace glimac {

	Objet3D::Objet3D(){

	}
	Objet3D::Objet3D(int identifiant, Model mod, string path, vec3 p, vec3 s, vec3 axeR, float angleR){
		id = identifiant;
		model = mod;
		emplacement = path;
		position = p;
		scaleObject = s;
		axeRotation = axeR;
		angleRotation=angleR;
	}
	Objet3D::Objet3D(string path){
		emplacement = path;
		model.loadModel(emplacement);
		position = glm::vec3(0.0f, -1.75f, -3.0f);
		scaleObject = glm::vec3(0.2f, 0.2f, 0.2f);
		axeRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		angleRotation = 0.0;
	}
	
	Objet3D::Objet3D(int identifiant, string path, vec3 p, vec3 s, vec3 axeR, float angleR){
		id = identifiant;
		emplacement = path;
		model.loadModel(emplacement);
		position = p;
		scaleObject = s;
		axeRotation = axeR;
		angleRotation=angleR;
	}
	Objet3D::Objet3D(int identifiant,vec3 p, vec3 s, vec3 axeR, float angleR){
		id = identifiant;
		position = p;
		scaleObject = s;
		axeRotation = axeR;
		angleRotation=angleR;
	}

	Objet3D::Objet3D(const Objet3D &o){
		id = o.id;
		model = o.model;
		emplacement = o.emplacement;
		position = o.position;
		scaleObject = o.scaleObject;
		axeRotation = o.axeRotation;
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
	void Objet3D::setRotation(vec3 newR,float newAngle){
		axeRotation = newR;
		angleRotation = newAngle;

	}

	vec3 Objet3D::getposition(){
		return position;
	}
	vec3 Objet3D::getscaleObject(){
		return scaleObject;
	}
	vec3 Objet3D::getaxeRotation(){
		return axeRotation;
	}
	float Objet3D::getangleRotation(){
		return angleRotation;
	}

	
	mat4 Objet3D::getModelMatrix(){
		mat4 modelMatrix  = mat4(1.0f);
        modelMatrix = translate(modelMatrix, position); 
        modelMatrix = scale(modelMatrix, scaleObject);
		modelMatrix = rotate(modelMatrix, radians(angleRotation), axeRotation);



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