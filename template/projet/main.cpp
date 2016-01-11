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
    int fullscreen = 0;
    while(!done) {
        // Event loop:
        finScene = myWorld.finScene();
        SDL_Event e;
        glm::ivec2 mousePos = windowManager.getMousePosition();
        while(windowManager.pollEvent(e)) {
            if((e.type == SDL_QUIT) || windowManager.isKeyPressed(SDLK_ESCAPE)) {
                done = true; // Leave the loop after this iteration
            }
            if((!myWorld.enPause()) && (!finScene)){
            
                if (windowManager.isKeyPressed(SDLK_UP)){
                    myWorld.trackCam.moveFront(-0.8);
                } 
                if (windowManager.isKeyPressed(SDLK_DOWN)) myWorld.trackCam.moveFront(0.3);
                    
                if (windowManager.isKeyPressed(SDLK_LEFT)) myWorld.trackCam.rotateLeft(-1.5);
                if (windowManager.isKeyPressed(SDLK_RIGHT)) myWorld.trackCam.rotateLeft(1.5);

                
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

              if ( windowManager.isKeyPressed(SDLK_f)) // Touche f
            {
                // Alterne du mode plein écran au mode fenêtré
                if ( fullscreen == 0 )
                {
                    fullscreen = 1;
                    SDL_SetWindowFullscreen(windowManager.getWindow() ,SDL_WINDOW_FULLSCREEN);
                }
                else if ( fullscreen == 1 )
                {
                    fullscreen = 0;
                    SDL_SetWindowFullscreen(windowManager.getWindow() ,0);
                }
            }
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
