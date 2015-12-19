#include <Core/TrajectoireCamera.hpp>
#include <iostream>

namespace glimac {
	TrajectoireCamera::TrajectoireCamera(int id, vec3 tableauPos[]){
		
		// //load
		this->id = id;
		
		int taille = 3;
		int i = 0;
		for(i=0; i<taille; i++)
		{
			position[i]=tableauPos[i];
		}

		idPositionActuel=0;

		//angle_actuel(0);
		
		
		


	}

	TrajectoireCamera::~TrajectoireCamera(){

	}

	void TrajectoireCamera::seDeplacer(){
		
	}
	void TrajectoireCamera::cameraRotation(){

	}

	mat3 pivotement(float angle){

	}

	mat3 position_suivante(int idPositionActuel, mat3 position){
		//transform();
	}

}