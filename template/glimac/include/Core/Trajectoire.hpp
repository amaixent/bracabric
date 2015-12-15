#pragma once
#include <glimac/glm.hpp>

using namespace glm;

namespace glimac {

class Trajectoire
{
private:
	int id;
	float angle_actuel;
	float position[];
	int id_position_actuel;
	float angle_zero[];
	
public:
	Trajectoire();
	~Trajectoire();

	void seDeplacer();
	mat3 pivotement(float angle);
	mat3 position_suivante();

	/* data */
};
}