#pragma once
#include <glimac/glm.hpp>

using namespace glm;

namespace glimac {

class TrajectoireCamera
{
private:
	int id;
	int taille;
	vec3 position[]; //c'est un vecteur de vecteur donc un mat3?
	int idPositionActuel;
	//float angle_actuel;
	//float angle_zero[];
	
public:
	TrajectoireCamera(int id, vec3 position[]);
	~TrajectoireCamera();

	void seDeplacer();
	void cameraRotation();
	mat3 pivotement(float angle);
	mat3 positionSuivante(int idPositionActuel, mat3 position);
	//load_trajectoire(fichier) a voir avec hamlet

	/* data */
};
}