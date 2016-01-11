#include "Core/Monde.hpp"

namespace glimac {
	Monde::Monde(GLuint width,GLuint height,SDLWindowManager &windowManager){
		
		panneauDebut.loadPanneau("assets/panneau/debut_scene.jpg");
		panneauLoading.loadPanneau("assets/panneau/loading.jpg");
		screenWidth = width;
		screenHeight = height;
		chargeScene(1,windowManager);
		pause = 1;
		changePause();

	}


	Monde::~Monde(){
	
	}

	void Monde::chargeScene(int identifiant,SDLWindowManager &windowManager){
		
		if (identifiant != myScene.getId())
		{	
			if (identifiant ==1)
			{
				this->myScene.chargeScene(1,"projet/shaders/lampe_torche.vs.glsl", "projet/shaders/normals.fs.glsl","projet/scenes/scene1/Tas.txt","assets/panneau/fin_scene1.jpg");
			}
			else if (identifiant == 2){
				loading(windowManager);
				this->myScene.chargeScene(2,"projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","projet/scenes/scene2/Tas.txt","assets/panneau/fin_scene2.jpg");
			}
			else if (identifiant == 3){
				loading(windowManager);
				this->myScene.chargeScene(3,"projet/shaders/lampe_torche.vs.glsl", "projet/shaders/lampe_torche.fs.glsl","projet/scenes/scene3/Tas.txt","assets/panneau/fin_scene3.jpg");
			}
			else if (identifiant ==0){
				this->myScene.changeScene();
				panneauDebut.fermeturePanneau();
				panneauLoading.fermeturePanneau();
			}
			
			trackCam.resetPositionInit(identifiant);
			
			
		}	
	}

	int Monde::getSceneId(){
		return myScene.getId();
	}

	//Moyen détourné de mettre le jeu en pause parce que si on appuie sur espace, 
	//la fonction est appelée plusieurs fois.
	void Monde::changePause(){
		if (pause == 3)
		{
			pause = 0;
			
		}
		else{
			pause++;
			
		}
	}
	bool Monde::enPause(){
		if (pause == 2){
			return true;
		}
		else{
			return false;
		}
	}
	void Monde::Draw(){
		if (enPause() && !finScene())
		{
			this->panneauDebut.Draw(this->trackCam,screenWidth,screenHeight);
		}
		else{
			float ZCam = trackCam.getm_fDistance();
			myScene.Draw(this->trackCam,screenWidth,screenHeight, ZCam);
		}
		finScene();
		
	}
	void Monde::loading(SDLWindowManager &windowManager){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    panneauLoading.Draw(trackCam,screenWidth,screenHeight);
    windowManager.swapBuffers();
}
	bool Monde::finScene(){
		float d = abs(trackCam.getm_fDistance());
		if( ((d - 50 >= 0) && (myScene.getId() == 1))
			|| ((d - 38 >= 0) && (myScene.getId() == 2))
			|| ((d - 56 >= 0) && (myScene.getId() == 3))
			)
		{
			myScene.panneauFin.Draw(trackCam,screenWidth,screenHeight);
			return true;
		}
		return false;
	}

}