#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Core/Objet3D.hpp"

using namespace glimac;

struct Node
{
    Objet3D value;
    struct Node * next;

};

typedef Node * List;

List createNode(Objet3D value);
int lengthList(List tete);
List insertHead(List tete, Objet3D value);
List insertToList(List tete, int index,Objet3D value);
List removeHead(List tete);



/* ATTENTION il faut remettre le pointeur de la liste à NULL
*   donc passage de l'adresse du pointeur
*/
void freeList(List * tete);
