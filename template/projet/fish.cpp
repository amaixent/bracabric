#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Core/Scene.hpp"

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


    //On Initialise la scene
    Scene maScene("projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","Le chemin du fichier pour loader les objets");

    // Initialisaton TrajCam
    mat3 positions = mat3(vec3(0.0f, 0.0f, 0.0f),vec3(0.0f, 0.0f, 5.0f),vec3(0.0f, 0.0f, 10.0f)); 
    TrajectoireCamera trajcam(1, positions);

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

                trajcam.rotateLeft(-2*mousePosX);
                trajcam.rotateUp(-2*mousePosY);
            }
                

                if (windowManager.isKeyPressed(SDLK_i)) trajcam.rotateUp(0.5);
                if (windowManager.isKeyPressed(SDLK_k)) trajcam.rotateUp(-0.5);
                if (windowManager.isKeyPressed(SDLK_j)) trajcam.rotateLeft(0.5);
                if (windowManager.isKeyPressed(SDLK_l)) trajcam.rotateLeft(-0.5);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //On nettoit la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(1.01f, 1.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        maScene.Draw(trajcam,screenWidth,screenHeight);



        // Update the display
        windowManager.swapBuffers();
    }



    return EXIT_SUCCESS;
}
