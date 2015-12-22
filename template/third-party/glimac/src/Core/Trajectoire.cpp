#include <Core/Trajectoire.hpp>
#include <iostream>

namespace glimac {
	Trajectoire::Trajectoire(int id, mat3 tableauPos){
		
		// //load
		this->id = id;
		
		position = tableauPos;
		idPositionActuel=0;

		//angle_actuel(0);
	
	}

	Trajectoire::~Trajectoire(){

	}

	void Trajectoire::seDeplacer(){
		
	}
	void Trajectoire::cameraRotation(){

	}

	mat3 pivotement(float angle){

	}

	mat3 position_suivante(int idPositionActuel, mat3 position){
		//transform();
	}

}