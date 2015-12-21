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
		m_Position = glm::vec3(0.0f);
		m_fPhi = M_PI;
		m_fTheta = 0.0;
		computeDirectionVectors();
	
	}

	TrajectoireCamera::~TrajectoireCamera(){

	}

	void TrajectoireCamera::computeDirectionVectors(){
		float radPhi = m_fPhi;
		float radTheta = m_fTheta;
		m_FrontVector = vec3(cos(radTheta)*sin(radPhi), sin(radTheta), cos(radTheta)*cos(radPhi));
		m_LeftVector = vec3(sin(radPhi+(M_PI/2.0)), 0, cos(radPhi+(M_PI/2.0)));
		m_UpVector = cross(m_FrontVector, m_LeftVector);
	}
	void TrajectoireCamera::rotateLeft(float degrees){
		float radian = degrees * M_PI/180;
		m_fPhi = m_fPhi + radian;
		computeDirectionVectors();	
	}

	void TrajectoireCamera::rotateUp(float degrees){
		float radian = degrees * M_PI/180;
		m_fTheta = m_fTheta + radian;
		computeDirectionVectors();		
	}

	mat4 TrajectoireCamera::getViewMatrix() const {
		mat4 VMatrix = lookAt(m_Position, m_FrontVector + m_Position, m_UpVector);
		return VMatrix;
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