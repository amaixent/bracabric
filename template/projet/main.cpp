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

    

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    //Initialisation du monde
    Monde myWorld;

    //FreeflyCamera freefly;
    //TrackballCamera trackCam;
 
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        glm::ivec2 mousePos = windowManager.getMousePosition();
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
             
                float mousePosX = mousePos.x/800.0f - 0.5;
                float mousePosY = mousePos.y/600.0f - 0.5;

                myWorld.trackCam.rotateLeft(2*mousePosX);
                myWorld.trackCam.rotateUp(2*mousePosY);
            }

                //if (windowManager.isKeyPressed(SDLK_z)) myWorld.trackCam.moveFront(-0.1);
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
                //if (windowManager.isKeyPressed(SDLK_q)) trackCam.moveLeft(-0.1);
                //if (windowManager.isKeyPressed(SDLK_d)) trackCam.moveLeft(0.1);
                
                if (windowManager.isKeyPressed(SDLK_UP)) myWorld.trackCam.rotateUp(-0.5); //avec la souris on a plus d'aisance, ces touches sont un plus
                if (windowManager.isKeyPressed(SDLK_DOWN)) myWorld.trackCam.rotateUp(0.5);
                if (windowManager.isKeyPressed(SDLK_LEFT)) myWorld.trackCam.rotateLeft(-0.5);
                if (windowManager.isKeyPressed(SDLK_RIGHT)) myWorld.trackCam.rotateLeft(0.5);

                if (windowManager.isKeyPressed(SDLK_v)) myWorld.chargeScene(1);
                if (windowManager.isKeyPressed(SDLK_b)) myWorld.chargeScene(2);
                if (windowManager.isKeyPressed(SDLK_n)) myWorld.chargeScene(3);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //On nettoit la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

      //  glClearColor(1.01f, 1.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        
        myWorld.Draw(screenWidth,screenHeight);



        // Update the display
        windowManager.swapBuffers();
    }


    myWorld.chargeScene(0);
    
    return EXIT_SUCCESS;
}
