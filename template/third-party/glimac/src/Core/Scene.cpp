#include "Core/Scene.hpp"


namespace glimac {
	Scene::Scene(string fichierVs,string fichierFs,string fichierObjet){
		shader.loadShader(fichierVs,fichierFs);
		ListObjet = NULL;
		ListObjet = Load2ObjetsTmp(ListObjet);

		// LoadObjectFromFile(fichierObjet,ListObjet);
		id = 0;
		idTrajectoire = 0;
	}

	Scene::~Scene(){
		delete(ListObjet); //ouai c'est fait à l'arrache ça il faudra (je libère que le premier élément de la liste) Maëlle.
	}

List Scene::Load2ObjetsTmp(List ListObjet){

	Objet3D nanosuit("assets/models/scene3/nanosuit/nanosuit.obj"); //Charge l'objet
	ListObjet=insertHead(ListObjet, nanosuit); //insert le noeud dans la liste.
	Objet3D maison("assets/models/scene3/house/fw43_lowpoly_n1.3ds");
	ListObjet= insertHead(ListObjet, maison);
	

	return ListObjet;	

}
	
List Scene::LoadObjectFromFile(string fichierObjet, List ListObjet){
	//bisou ALICE!!
}

void Scene::Draw(Trajectoire trajcam, FreeflyCamera camera, GLuint screenWidth, GLuint screenHeight){

	shader.Use();   // <-- Don't forget this one!
        
    // Transformation matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);/*aiMemoryInfo::cameras.Zoom*/
    glm::mat4 view = camera.getViewMatrix();//aiMemoryInfo::cameras.GetViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    //Draw the loaded model
   	List ListeParcourue = ListObjet;
   	Objet3D objet_tmp;
   	glm::mat4 modelMatrix;

   	//On parcourt la liste et on dessine chaque élément.
    while(ListeParcourue){
    	objet_tmp = ListeParcourue->value;

    	modelMatrix = objet_tmp.getModelMatrix(); //Ici value est un objet3D voir liste_Objet3D.c
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        objet_tmp.Draw(shader);

    	ListeParcourue=ListeParcourue->next;//Passage à l'élément suivant de la liste.
    }
}

}