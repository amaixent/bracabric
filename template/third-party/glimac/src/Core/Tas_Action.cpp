#include <Core/Tas_Action.hpp>

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
void Scene3_MouvementCamel(int idTas, string emplacement,Objet3D* o){
	if ((emplacement[19] == '3') && (idTas == 4))// on veut faire bouger le Tas 5 de la scène 3
	{
		vec3 R = o->getangleRotation();
		if (o->getId()<8)
		{
			R[1]+=1.9;
		}
			
		o->setRotation(R);
	}
}
void Scene3_MouvementWaffle(int idTas, string emplacement,Objet3D* o){
	if ((emplacement[19] == '3') && (idTas == 2))// on veut faire bouger le Tas 5 de la scène 3
	{
		vec3 S = o->getscaleObject();
		int a;
		a = (int(S[1]*1000)%2);

		// if (S[1]<=0.02)
		// {
		// 	if ((int(S[1]*1000)%2)==0)
		// 	{
		// 		S-=vec3(0.002,0.002,0.002);
		// 	}
		// 	else{
		// 		//S+=vec3(0.002,0.002,0.002);
		// 	}

		// 	if (S[1]<=0.00002)
		// 	{
		// 		//S+=vec3(0.001,0.001,0.001);
		// 	}
		// 	o->setScale(S);
		// }
		// else{
		// 	o->setScale(vec3(0.02,0.02,0.02));
		// }
			
		
	}
}

void ActionTas(int idTas, string emplacement,Objet3D* o){
	Scene3_MouvementBird(idTas, emplacement,o);
	Scene3_MouvementCamel(idTas, emplacement, o);
	Scene3_MouvementWaffle(idTas, emplacement, o);
}