
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

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

    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader ourShader("projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl");

    // Load models

    Model ourModel2("assets/models/scene3/house/fw43_lowpoly_n1.3ds");
    Model ourModel("assets/models/scene3/nanosuit/nanosuit.obj");

   // Model ourModel("assets/OBJET3D/Animaux/fish.3DS");

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/



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

        //On nettoit la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

         glClearColor(1.01f, 1.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();   // <-- Don't forget this one!
        // // Transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);/*aiMemoryInfo::cameras.Zoom*/
        glm::mat4 view = glm::mat4(1.0);//aiMemoryInfo::cameras.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model2;
        model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, -5.0f)); // Translate it down a bit so it's at the center of the scene
        model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f)); // It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        ourModel2.Draw(ourShader);

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, -5.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        
        ourModel.Draw(ourShader);



        // Update the display
        windowManager.swapBuffers();
    }



    return EXIT_SUCCESS;
}
