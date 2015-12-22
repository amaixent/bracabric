#pragma once
#include <glimac/glm.hpp>

using namespace glm;



class FreeflyCamera 
{
private:
	vec3 m_Position;
	float m_fPhi;
	float m_fTheta;
	vec3 m_FrontVector;
	vec3 m_LeftVector;
	vec3 m_UpVector;

	void computeDirectionVectors();

public:
	FreeflyCamera();
	~FreeflyCamera();

	void rotateLeft(float degrees);
	void rotateUp(float degrees);
	mat4 getViewMatrix() const;
};
