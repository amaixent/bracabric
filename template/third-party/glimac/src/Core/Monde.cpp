#include "Core/Monde.hpp"

namespace glimac {
	Monde::Monde(){
		chargeScene(1);
	}

	Monde::~Monde(){

	}

	void Monde::chargeScene(int identifiant){
		if (identifiant != myScene.getId())
		{	if (identifiant ==1)
			{
				this->myScene.chargeScene(1,"projet/shaders/lampe_torche.vs.glsl", "projet/shaders/normals.fs.glsl","projet/scenes/scene1/Tas.txt", "assets/skybox/sea/");
			}
			else if (identifiant == 2){
				this->myScene.chargeScene(2,"projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","projet/scenes/scene2/Tas.txt", "assets/skybox/sea/");
			}
			else if (identifiant == 3){
				this->myScene.chargeScene(3,"projet/shaders/model_loading.vs.glsl", "projet/shaders/model_loading.fs.glsl","projet/scenes/scene3/Tas.txt", "assets/skybox/sea/");
			}
			else if (identifiant ==0){
				this->myScene.changeScene();
			}
		
		}	
	}

	void Monde::Draw(Trajectoire trajcam, TrackballCamera camera, GLuint screenWidth, GLuint screenHeight){
		myScene.Draw(trajcam,camera,screenWidth,screenHeight);
	}

}