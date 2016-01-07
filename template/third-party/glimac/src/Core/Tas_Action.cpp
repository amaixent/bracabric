#include <Core/Tas_action.hpp>

using namespace glimac;

void Scene3_MouvementBird(int idTas, string emplacement,Objet3D* o){
	if ((emplacement[19] == '3') && (idTas == 5))// on veut faire bouger le Tas 5 de la scène 3
	{
		vec3 R = o->getangleRotation();
		int id= o->getId();
		if (id%2==0)
		{
			R[1]+=0.4;
		}
		else{
			R[1]-=0.4;
		}
		
		o->setRotation(R);
	}
}

void ActionTas(int idTas, string emplacement,Objet3D* o){
	Scene3_MouvementBird(idTas, emplacement,o);
}