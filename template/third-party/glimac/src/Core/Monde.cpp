#include "Core/Monde.hpp"

namespace glimac {
	Monde::Monde(){
		//panneauDebut.loadPanneau("assets/panneau/debut_scene.jpg");
		chargeScene(1);
	}


	Monde::~Monde(){
	
	}

	void Monde::chargeScene(int identifiant){
		if (identifiant != myScene.getId())
		{	if (identifiant ==1)
			{
				this->myScene.chargeScene(1,"projet/shaders/lampe_torche.vs.glsl", "projet/shaders/normals.fs.glsl","projet/scenes/scene1/Tas.txt", "assets/skybox/hw_nightsky/");
			}
			else if (identifiant == 2){
				//this->panneauDebut.Draw();
				this->myScene.chargeScene(2,"projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","projet/scenes/scene2/Tas.txt", "assets/skybox/sea/");
			}
			else if (identifiant == 3){
				this->myScene.chargeScene(3,"projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","projet/scenes/scene3/Tas.txt", "assets/skybox/blood/");
			}
			else if (identifiant ==0){
				this->myScene.changeScene();
				//this->panneauDebut.fermeturePanneau();
			}
			
			trackCam.resetPositionInit(identifiant);
		}	
	}

	int Monde::getSceneId(){
		return myScene.getId();
	}
	void Monde::Draw(GLuint screenWidth, GLuint screenHeight){
		myScene.Draw(this->trackCam,screenWidth,screenHeight);
	}

}