
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <Core/Trajectoire.hpp>
#include <Camera/FreeflyCamera.hpp>


#include "Shader_site.hpp"
#include "Model.hpp"

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

    mat3 positions = mat3(vec3(0.0f, 0.0f, 0.0f),vec3(0.0f, 0.0f, 5.0f),vec3(0.0f, 0.0f, 10.0f)); 

    Trajectoire trajectoire(1, positions);

    FreeflyCamera freefly;

    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader ourShader("projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl");

    // Load models

    Model ourModel2("assets/models/scene3/house/fw43_lowpoly_n1.3ds");
    Model ourModel("assets/models/scene3/nanosuit/nanosuit.obj");

    //Model ourModel2("assets/models/scene1/Spherical_Maze.obj");

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/



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

                freefly.rotateLeft(-2*mousePosX);
                freefly.rotateUp(-2*mousePosY);
            }
                
                if (windowManager.isKeyPressed(SDLK_i)) freefly.rotateUp(0.5);
                if (windowManager.isKeyPressed(SDLK_k)) freefly.rotateUp(-0.5);
                if (windowManager.isKeyPressed(SDLK_j)) freefly.rotateLeft(0.5);
                if (windowManager.isKeyPressed(SDLK_l)) freefly.rotateLeft(-0.5);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //On nettoit la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

         glClearColor(1.01f, 1.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();   // <-- Don't forget this one!
        // Transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);/*aiMemoryInfo::cameras.Zoom*/
        glm::mat4 view = freefly.getViewMatrix();//aiMemoryInfo::cameras.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //Draw the loaded model
        glm::mat4 model2;
        model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, -5.0f)); // Translate it down a bit so it's at the center of the scene
        model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));// It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        ourModel2.Draw(ourShader);

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, -3.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        
        ourModel.Draw(ourShader);



        // Update the display
        windowManager.swapBuffers();
    }



    return EXIT_SUCCESS;
}
