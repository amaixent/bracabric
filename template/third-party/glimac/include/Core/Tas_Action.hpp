#pragma once
#include "Core/Tas.hpp"
#include "glimac/glm.hpp"

using namespace glimac;

void Scene1_Mouvementd12(int idTas, string emplacement,Objet3D* o);
void Scene1_MouvementSphere(int idTas, string emplacement,Objet3D* o);

void Scene2_MouvementHippo(int idTas, string emplacement, Objet3D* o2);
void Scene2_MouvementCellRain(int idTas, string emplacement, Objet3D* o2);
void Scene2_MouvementGalaxieQueen(int idTas, string emplacement, Objet3D* o2);

void Scene3_MouvementBird(int idTas,string emplacement,Objet3D* o);
void Scene3_MouvementCamel(int idTas, string emplacement,Objet3D* o);
void Scene3_MouvementWaffle(int idTas, string emplacement,Objet3D* o);

void ActionTas(int idTas, string emplacement, Objet3D* o);