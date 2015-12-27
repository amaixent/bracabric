#include "Core/Scene.hpp"


namespace glimac {
	Scene::Scene(string fichierVs, string fichierFs, string fichierObjet){
		shader.loadShader(fichierVs, fichierFs);
		ListObjet = NULL;
		//ListObjet = Load2ObjetsTmp(ListObjet);

		ListObjet = LoadObjectFromFile(fichierObjet, ListObjet);
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

/*
Lecture du fichier texte directement ligne par ligne
"contenu" comporte chaque caractère de la ligne lue à chaque tour de boucle
remplir la liste de paramètres "objet" avec les éléments qui sont dans "contenu"
instancier les objets 3D à l'aide de ces paramètres après les avoir convertis dans le bon format
*/
	
List Scene::LoadObjectFromFile(string fichierObjet, List ListObjet){
	ifstream fichier(fichierObjet);
    //int NB_PARAMS_OBJET = 11;
    string contenu, temp, caractere, path;
    vec3 po, sc, ro;
    int id;
    float convertedToFloat[11];
    if(fichier)
    {
    	while(getline(fichier, contenu)){
    		caractere = contenu[0];
    		if(caractere != "#"){
			    
			    stringstream ss(contenu);
			    vector<string> objet;
			    while (ss >> temp)
			        objet.push_back(temp);

			    //Conversion dans le bon format (int pour l'id, float pour le reste)
				stringstream convert0(objet[0]);
				convert0 >> id;
				for(int i = 2; i < 10; i++){
					stringstream convert(objet[i]);
					convert >> convertedToFloat[i];
				}
			    path = objet[1];
				po = vec3(convertedToFloat[2], convertedToFloat[3], convertedToFloat[4]);
				sc = vec3(convertedToFloat[5], convertedToFloat[6], convertedToFloat[7]);
				ro = vec3(convertedToFloat[8], convertedToFloat[9], convertedToFloat[10]);

			    Objet3D newObjet(id, path, po, sc, ro);
				ListObjet = insertHead(ListObjet, newObjet);
    		}
    	}
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier : " << fichierObjet << endl;
    
	return ListObjet;
}

void Scene::Draw(Trajectoire trajcam, TrackballCamera camera, GLuint screenWidth, GLuint screenHeight){

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