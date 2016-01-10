#include "Core/Monde.hpp"

namespace glimac {
	Monde::Monde(GLuint width,GLuint height){
		
		panneauDebut.loadPanneau("assets/panneau/debut_scene.jpg");
		panneauLoading.loadPanneau("assets/panneau/loading.jpg");
		pause = true;
		screenWidth = width;
		screenHeight = height;
		chargeScene(1);

	}


	Monde::~Monde(){
	
	}

	void Monde::chargeScene(int identifiant){
		//this->panneauLoading.Draw(this->trackCam,screenWidth,screenHeight);
		if (identifiant != myScene.getId())
		{	
			if (identifiant ==1)
			{
				this->myScene.chargeScene(1,"projet/shaders/lampe_torche.vs.glsl", "projet/shaders/normals.fs.glsl","projet/scenes/scene1/Tas.txt");
			}
			else if (identifiant == 2){
				//this->panneauDebut.Draw();
				this->myScene.chargeScene(2,"projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","projet/scenes/scene2/Tas.txt");
			}
			else if (identifiant == 3){
				//this->myScene.chargeScene(3,"projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","projet/scenes/scene3/Tas.txt");
				this->myScene.chargeScene(3,"projet/shaders/lampe_torche.vs.glsl", "projet/shaders/lampe_torche.fs.glsl","projet/scenes/scene3/Tas.txt");
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
	void Monde::Draw(){
		if (pause != 3)
		{
			this->panneauDebut.Draw(this->trackCam,screenWidth,screenHeight);
		}
		else{
			myScene.Draw(this->trackCam,screenWidth,screenHeight);
		}
		
	}

}