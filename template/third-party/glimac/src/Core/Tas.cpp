#include <Core/Tas.hpp>

using namespace glimac;

	Tas::Tas(int identifiant,List ListO,vec3 p,vec3 s,vec3 axeR,float angleR){
		id = identifiant;
		ListObjet = ListO;
		position = p;
		scaleTas = s;
		axeRotation = axeR;
		angleRotation = angleR;
	}

	Tas::Tas(int identifiant,string fichierObjet,vec3 p,vec3 s,vec3 axeR,float angleR){
		id = identifiant;
		ListObjet = NULL;
		ListObjet = LoadObjectFromFile(fichierObjet,ListObjet);
		position = p;
		scaleTas = s;
		axeRotation = axeR;
		angleRotation = angleR;
	}

	Tas::Tas(){
		ListObjet = NULL;
	}
	
	Tas::~Tas(){
		//Libérer la mémoir pour les listes d'objets.
	}
/*
Lecture du fichier texte directement ligne par ligne
"contenu" comporte chaque caractère de la ligne lue à chaque tour de boucle
remplir la liste de paramètres "objet" avec les éléments qui sont dans "contenu"
instancier les objets 3D à l'aide de ces paramètres après les avoir convertis dans le bon format
*/

List Tas::LoadObjectFromFile(string fichierObjet, List ListObjet){
	ifstream fichier(fichierObjet);
    //int NB_PARAMS_OBJET = 11;
    string contenu, temp, caractere, path;
    vec3 po, sc, ro;
    int id;
    float angleRo;
    float convertedToFloat[12];
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
				for(int i = 2; i < 12; i++){
					stringstream convert(objet[i]);
					convert >> convertedToFloat[i];
				}
			    path = objet[1];
				po = vec3(convertedToFloat[2], convertedToFloat[3], convertedToFloat[4]);
				sc = vec3(convertedToFloat[5], convertedToFloat[6], convertedToFloat[7]);
				ro = vec3(convertedToFloat[8], convertedToFloat[9], convertedToFloat[10]);
				angleRo = convertedToFloat[11];
			    Objet3D newObjet(id, path, po, sc, ro, angleRo);
				ListObjet = insertHead(ListObjet, newObjet);

    		}
    	}
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier : " << fichierObjet << endl;
    
	return ListObjet;
}

mat4 Tas::getModelMatrixTas(Objet3D obj){
		mat4 modelMatrix  = mat4(1.0f);
        modelMatrix = translate(modelMatrix, position);
        modelMatrix = translate(modelMatrix, obj.getposition()); 
        
        modelMatrix = scale(modelMatrix, scaleTas);
        modelMatrix = scale(modelMatrix, obj.getscaleObject());

        if(axeRotation!=vec3(0,0,0))
        modelMatrix = rotate(modelMatrix, radians(angleRotation), axeRotation);
        if(obj.getaxeRotation()!=vec3(0,0,0))
        modelMatrix = rotate(modelMatrix, radians(obj.getangleRotation()), obj.getaxeRotation());

        return modelMatrix;
}

List Tas::getListObjet(){
	return ListObjet;
}

void Tas::Draw(Shader shader){
	//Draw the loaded model
   	List ListeParcourue = ListObjet;
   	Objet3D objet_tmp;
   	glm::mat4 modelMatrix = glm::mat4(1.0f);

   	//On parcourt la liste et on dessine chaque élément.
    while(ListeParcourue){
    	objet_tmp = ListeParcourue->value;//Ici value est un objet3D voir liste_Objet3D.c
    	modelMatrix = getModelMatrixTas(ListeParcourue->value);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        objet_tmp.Draw(shader);

    	ListeParcourue=ListeParcourue->next;//Passage à l'élément suivant de la liste.
    }
}
