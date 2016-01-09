#pragma once

#include <cstdint>
#include <SDL/SDL.h>
#include "glimac/glm.hpp"
#pragma once

namespace glimac {

class TrackballCamera {

private:
    float m_fDistance; //distance par rapport au centre de la scène
    float m_fAngleX; // l'angle effectué par la caméra autour de l'axe x de la scène (rotation vers le haut ou vers le bas)
    float m_fAngleY; //l'angle effectué par la caméra autour de l'axe y de la scène (rotation vers la gauche ou vers la droite)

public:

    TrackballCamera(); //Constructeur
   ~TrackballCamera(); //Destructeur

    void moveFront(float delta); //permettant d'avancer / reculer la caméra. Lorsque delta est positif la caméra doit avancer, sinon elle doit reculer.
    float getm_fDistance();
    void resetPositionInit(int identifiant);
    void rotateLeft(float degrees); //permettant de tourner latéralement autour du centre de vision.
    float getm_fAngleX();
    void resetm_fAngleX();
    float getm_fAngleY();
    void resetm_fAngleY(float angle);
    void rotateUp(float degrees); //permettant de tourner verticalement autour du centre de vision.
    void chemin();
    glm::mat4 getViewMatrix() const;
};

}
