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

		
				limiteLeft();

		m_FrontVector = vec3(cos(radTheta)*sin(radPhi), sin(radTheta), cos(radTheta)*cos(radPhi));
		m_LeftVector = vec3(sin(radPhi+(M_PI/2.0)), 0, cos(radPhi+(M_PI/2.0)));
		m_UpVector = cross(m_FrontVector, m_LeftVector);
		std::cout<<"m_LeftVector : "<< m_LeftVector.x <<std::endl;
	}

	void FreeflyCamera::limiteLeft(){
		// if (m_fPhi > 89.0)

	 //        m_fPhi = 89.0;

	 //    else if (m_fPhi < -89.0)

	 //        m_fPhi = -89.0;
		if (m_LeftVector.x > -1.222 && m_LeftVector.z<-0.993)
		{
			m_LeftVector = vec3(1.222, 0.0, -0.993);
		}
		else if (m_LeftVector.x > 0.105 && m_LeftVector.z<0.995)
		{
			m_LeftVector = vec3(0.105, 0.0, 0.995);
		}
	}

	// void FreeflyCamera::limiteUp(){

	// }

	void FreeflyCamera::rotateLeft(float degrees){
		//limiteLeft(degrees);
		float radian = degrees * M_PI/180;
		m_fPhi = m_fPhi + radian;

		//std::cout<<"m_fPhi : "<< m_fPhi <<std::endl;
		computeDirectionVectors();	
	}

	void FreeflyCamera::rotateUp(float degrees){
		float radian = degrees * M_PI/180;
		m_fTheta = m_fTheta + radian;
		computeDirectionVectors();		
	}
	void FreeflyCamera::moveLeft(float t){
		m_Position += t * m_LeftVector;
		computeDirectionVectors();
	}

	void FreeflyCamera::moveFront(float t){
		m_Position += t * m_FrontVector;
		computeDirectionVectors();
	}
	
	mat4 FreeflyCamera::getViewMatrix() const {
		mat4 VMatrix = lookAt(m_Position, m_FrontVector + m_Position, m_UpVector);
		return VMatrix;
	}

