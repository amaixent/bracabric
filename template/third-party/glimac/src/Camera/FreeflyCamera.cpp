#include <Camera/FreeflyCamera.hpp>
#include <iostream>


	FreeflyCamera::FreeflyCamera(){
		m_Position = glm::vec3(0.0f);
		m_fPhi = M_PI;
		m_fTheta = 0.0;
		computeDirectionVectors();
	}

	FreeflyCamera::~FreeflyCamera(){

	}

	void FreeflyCamera::computeDirectionVectors(){
		float radPhi = m_fPhi;
		float radTheta = m_fTheta;
		m_FrontVector = vec3(cos(radTheta)*sin(radPhi), sin(radTheta), cos(radTheta)*cos(radPhi));
		m_LeftVector = vec3(sin(radPhi+(M_PI/2.0)), 0, cos(radPhi+(M_PI/2.0)));
		m_UpVector = cross(m_FrontVector, m_LeftVector);
	}
	void FreeflyCamera::rotateLeft(float degrees){
		float radian = degrees * M_PI/180;
		m_fPhi = m_fPhi + radian;
		computeDirectionVectors();	
	}

	void FreeflyCamera::rotateUp(float degrees){
		float radian = degrees * M_PI/180;
		m_fTheta = m_fTheta + radian;
		computeDirectionVectors();		
	}

	mat4 FreeflyCamera::getViewMatrix() const {
		mat4 VMatrix = lookAt(m_Position, m_FrontVector + m_Position, m_UpVector);
		return VMatrix;
	}

