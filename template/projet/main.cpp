#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Core/Monde.hpp"


using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    GLuint screenWidth = 800, screenHeight = 600;

    SDLWindowManager windowManager(screenWidth, screenHeight, "Bracabric");

    glewExperimental = GL_TRUE;
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    //Initialisation du monde
    Monde myWorld(screenWidth,screenHeight,windowManager);


    // Application loop:
    bool done = false;
    bool finScene = false;
    while(!done) {
        // Event loop:
        finScene = myWorld.finScene();
        SDL_Event e;
        glm::ivec2 mousePos = windowManager.getMousePosition();
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if((!myWorld.enPause()) && (!finScene)){
                if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
                 
                    float mousePosX = mousePos.x/(float)screenWidth - 0.5;
                    float mousePosY = mousePos.y/(float)screenWidth - 0.5;

                    myWorld.trackCam.rotateLeft(2*mousePosX);
                    myWorld.trackCam.rotateUp(2*mousePosY);
                }

                if (windowManager.isKeyPressed(SDLK_z)){

                    if((myWorld.trackCam.getm_fAngleX()) == 0 && (myWorld.trackCam.getm_fAngleY() == 0)){
                            myWorld.trackCam.moveFront(-0.1);
                    }

                    if((myWorld.trackCam.getm_fAngleX() != 0) || (myWorld.trackCam.getm_fAngleY() != 0)) {
                            myWorld.trackCam.resetm_fAngleX();
                            myWorld.trackCam.resetm_fAngleY();
                    }
                } 
                if (windowManager.isKeyPressed(SDLK_s)) {
                    myWorld.trackCam.moveFront(0.1);
                    if(myWorld.trackCam.getm_fDistance() == 0.0) std::cout<<"Pour un point de vue plus large, aller dans TrackballCamera.cpp et suivre les indics :)"<<std::endl;
                }

                if (windowManager.isKeyPressed(SDLK_UP)) myWorld.trackCam.rotateUp(-0.5); //avec la souris on a plus d'aisance, ces touches sont un plus
                if (windowManager.isKeyPressed(SDLK_DOWN)) myWorld.trackCam.rotateUp(0.5);
                if (windowManager.isKeyPressed(SDLK_LEFT)) myWorld.trackCam.rotateLeft(-0.5);
                if (windowManager.isKeyPressed(SDLK_RIGHT)) myWorld.trackCam.rotateLeft(0.5);

                
                //On garde la liberté de changer à tout moment de scene pour la soutenance
                if (windowManager.isKeyPressed(SDLK_v)) myWorld.chargeScene(1,windowManager);
                if (windowManager.isKeyPressed(SDLK_b)) myWorld.chargeScene(2,windowManager);
                if (windowManager.isKeyPressed(SDLK_n)) myWorld.chargeScene(3,windowManager);
            }
            //Choix de la scene à charger quand on arrive à la fin d'une scene
            if(finScene){
                finScene = false;

                if (windowManager.isKeyPressed(SDLK_q)) {
                    
                    if (myWorld.getSceneId() == 1) myWorld.chargeScene(2,windowManager);
                    else if (myWorld.getSceneId() == 2) myWorld.chargeScene(1,windowManager);
                    else if (myWorld.getSceneId() == 3) myWorld.chargeScene(1,windowManager);
                }
                if (windowManager.isKeyPressed(SDLK_d)) {
                    if (myWorld.getSceneId() == 1) myWorld.chargeScene(3,windowManager);
                    else if (myWorld.getSceneId() == 2) myWorld.chargeScene(3,windowManager);
                    else if (myWorld.getSceneId() == 3) myWorld.chargeScene(2,windowManager);
                }
                
            }

            if (windowManager.isKeyPressed(SDLK_SPACE)) myWorld.changePause();
            // if (windowManager.isKeyPressed(SDLK_q)) done = true; //pour pouvoir quitter si jamais il y a un problème avec le plein écran

            // //test sur un événement
            // if(e.type == SDL_WINDOWEVENT_SIZE_CHANGED){
            //     screenWidth = e.window.data1;
            //     screenHeight = e.window.data2;
            //     SDL_SetWindowSize(windowManager.getWindow(), screenWidth, screenHeight);
            //     std::cout << "changed !" << e.window.data1 << e.window.data2 << std::endl;
            // }
            // //essai sur un autre événement pour voir mais en fait non ça ne passe pas !
            // if (e.type == SDL_WINDOWEVENT_RESIZED){
            //     screenWidth  = e.window.data1;
            //     screenHeight = e.window.data2;
            //     SDL_SetWindowSize(windowManager.getWindow(), screenWidth, screenHeight);
            //     std::cout << "resized !" << e.window.data1 << e.window.data2 << std::endl;
            // }
        }
        //On nettoit la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myWorld.Draw();

        // Update the display
        windowManager.swapBuffers();
    }


    myWorld.chargeScene(0,windowManager);
    
    return EXIT_SUCCESS;
}
