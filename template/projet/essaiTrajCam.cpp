#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <Core/TrajectoireCamera.hpp>

using namespace glimac;
using namespace glm;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    glewExperimental = GL_TRUE;

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     /*********Essaie trajectoire à la main**********/

    vec3 position1 = vec3(0.0f, 0.0f, 0.0f);
    vec3 position2 = vec3(0.0f, 0.0f, 5.0f);
    vec3 position3 = vec3(0.0f, 0.0f, 10.0f);

    vec3 tableau_position[3];
    tableau_position[0] = position1;
    tableau_position[1] = position2;
    tableau_position[2] = position3;

    TrajectoireCamera trajectoire(1, tableau_position);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
