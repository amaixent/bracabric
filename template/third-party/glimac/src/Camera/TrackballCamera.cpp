#include "Camera/TrackballCamera.hpp"
#include <iostream>
#include <math.h>

namespace glimac {

    TrackballCamera::TrackballCamera() {
         m_fDistance = 0.0;
         m_fAngleX = 0.0;
         m_fAngleY = 0.0;
         //isLookingAilleurs = 0;
    }

    TrackballCamera::~TrackballCamera() {
    }

    void TrackballCamera::moveFront(float delta) {
         m_fDistance += delta;
         //      std::cout<<time(NULL)/14000<<std::endl;
          //if(m_fAngleY != 0.0) isLookingAilleurs = 1;
        //else if(m_fAngleY == 0.0) isLookingAilleurs = 0;
          //std::cout<<"isLookingAilleurs"<<isLookingAilleurs<<std::endl;

        /*On peut avancer et reculer mais on ne peut pas aller derrière le point de départ ! */
        /****Salut, boucle à désactiver pour placer les objets 3D****/
        if (m_fDistance>0.0)
        {
          m_fDistance =0.0;
        }
    }
    
    float TrackballCamera::getm_fDistance(){
      return m_fDistance;
    }

    void TrackballCamera::resetPositionInit(int identifiant){
        m_fDistance = 0.0;  
        m_fAngleX = 0.0;
        m_fAngleY = 0.0;
    }


    void TrackballCamera::rotateLeft(float degrees) {
        m_fAngleX += degrees / 180 * M_PI;
        
        if (m_fAngleX > 1.20)

            m_fAngleX = 1.20;

        else if (m_fAngleX < -1.25)

             m_fAngleX = -1.25;

    } 

    float TrackballCamera::getm_fAngleX(){
      return m_fAngleX;
    }

    void TrackballCamera::resetm_fAngleX(){
        m_fAngleX = 0.0;
    }

    void TrackballCamera::rotateUp(float degrees){
         m_fAngleY += degrees / 180 * M_PI;
    
          if (m_fAngleY > 0.95)

            m_fAngleY = 0.95;

        else if (m_fAngleY < -1.11)

             m_fAngleY = -1.11;
    }

    float TrackballCamera::getm_fAngleY(){
      return m_fAngleY;
    }

    void TrackballCamera::resetm_fAngleY(){
        m_fAngleY = 0.0;
    }
    void TrackballCamera::retourSlowMotion(float degrees){
    

          if(m_fAngleX>0.0)
          m_fAngleX -= degrees / 180 * M_PI;
        else m_fAngleX += degrees / 180 * M_PI;

        // if(isLookingAilleurs == 1){
        //     if(m_fAngleY>0.0){
        //        std::cout<<"m_fAngleY"<<std::endl;

        //         m_fAngleY-=0.001;
        
        //     }
        //     else {
              
        //         m_fAngleY+=0.001;
        //        std::cout<<"coucou2"<<std::endl;

        //     }
        //           std::cout<<m_fAngleY<<std::endl;

        // if(m_fAngleY=0.0) isLookingAilleurs=0;
        // }
    }
    glm::mat4 TrackballCamera::getViewMatrix() const{

        glm::mat4 MatrixId = glm::mat4(1.0); //Matrice Identité

        glm::mat4 matrixMoveFront = glm::translate( MatrixId, glm::vec3(0.0f, 0.0f, -m_fDistance) ); //Translation en z
        glm::mat4 matrixrotateLeft = glm::rotate( MatrixId, m_fAngleX, glm::vec3(0, 1, 0) ); //Axe x
        glm::mat4 matrixrotateUp = glm::rotate( MatrixId, m_fAngleY, glm::vec3(1, 0, 0) ); //Axe y

    
        return matrixrotateLeft * matrixrotateUp*matrixMoveFront;
    }

}
