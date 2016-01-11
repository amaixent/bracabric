#include <Core/Tas_Action.hpp>

using namespace glimac;

void Scene1_Mouvementd12(int idTas, string emplacement,Objet3D* o){
	if ((emplacement[19] == '1') && (idTas ==1))// on veut faire bouger le Tas 1 de la scène 1
	{
		vec3 R = o->getangleRotation();
		int id = o->getId();
		if (id % 2 == 0) R[1] += 0.6;
		else R[1] -= 0.6;
		o->setRotation(R);
	}
}

void Scene1_MouvementSphere(int idTas, string emplacement,Objet3D* o){
if ((emplacement[19] == '1') && (idTas == 5))// on veut faire bouger le Tas 5 de la scène 1
	{
		vec3 T = o->getposition();
		//std::cout << T[1] << std::endl;
		if (T[1]<=0.7) {
			if ((int(T[1]*100)%2)==0) T-=vec3(0.004,0.004,0.004);
			else  T+=vec3(0.004,0.004,0.004);
			if (T[1]<=0.00004) T+=vec3(0.001,0.001,0.001);
			o->setPosition(T);
		}
		else o->setPosition(vec3(0.004,0.004,0.004));
	}
}

void Scene2_MouvementHippo(int idTas, string emplacement, Objet3D* o){
	if ((emplacement[19] == '2') && (idTas == 0)) {
		vec3 R = o->getangleRotation();
		int id= o->getId();
		if (id%2==1) R[1]-=0.8;
		

		R[0]+=0.8;
		R[1]-=0.8;
		R[2]-=0.8;
		
		o->setRotation(R);
	}
}

void Scene2_MouvementCellRain(int idTas, string emplacement, Objet3D* o){
	if ((emplacement[19] == '2') && (idTas == 1)) {
		vec3 R = o->getangleRotation();
		int id= o->getId();
		if (id%2==1) R[1]-=0.8;
		if (id%2==0){
			R[1]+=0.4;
			R[2]+=0.4;
		} 
		o->setRotation(R);
	}
}

void Scene2_MouvementGalaxieQueen(int idTas, string emplacement, Objet3D* o){
	if ((emplacement[19] == '2') && (idTas == 5)) {
		vec3 R = o->getangleRotation();
		int id = o->getId();
		R[2] -= 1.0;
		o->setRotation(R);
	}
}

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
	if ((emplacement[19] == '3') && (idTas == 4))// on veut faire bouger le Tas 4 de la scène 3
	{
		vec3 R = o->getangleRotation();
		if (o->getId()<8)
		{
			R[1]+=1.9;
		}	
		o->setRotation(R);

	}
}


void ActionTas(int idTas, string emplacement,Objet3D* o){
	Scene1_Mouvementd12(idTas, emplacement, o);
	Scene1_MouvementSphere(idTas, emplacement,o);
	Scene2_MouvementHippo(idTas, emplacement, o);
	Scene2_MouvementCellRain(idTas, emplacement, o);
	Scene3_MouvementBird(idTas, emplacement,o);
	Scene3_MouvementCamel(idTas, emplacement, o);
	Scene2_MouvementGalaxieQueen(idTas, emplacement, o);
}