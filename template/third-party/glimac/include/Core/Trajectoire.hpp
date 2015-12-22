#pragma once
#include <glimac/glm.hpp>

using namespace glm;

namespace glimac {

class Trajectoire
{
private:
	int id;
	mat3 position;//c'est un vecteur de vecteur donc un mat3?
	int idPositionActuel;
	//float angle_actuel;
	//float angle_zero[];


public:
	Trajectoire(int id, mat3 position);
	~Trajectoire();

	void seDeplacer();
	void cameraRotation();
	mat3 pivotement(float angle);
	mat3 positionSuivante(int idPositionActuel, mat3 position);
	//load_trajectoire(fichier) a voir avec hamlet
	
};
}