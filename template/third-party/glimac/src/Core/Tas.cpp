#include <Core/Tas.hpp>

using namespace glimac;

	Tas::Tas(int identifiant,vec3 p,vec3 s,vec3 angleR){
		id = identifiant;
		position = p;
		scaleTas = s;
		angleRotation = angleR;
	}

	Tas::Tas(int identifiant,string fichierObjet,vec3 p,vec3 s,vec3 angleR){
		id = identifiant;
		LoadObjectFromFile(fichierObjet);
		position = p;
		scaleTas = s;
		angleRotation = angleR;
	}

	Tas::Tas(){
	}
	
	Tas::~Tas(){
		
	}
/*
Lecture du fichier texte directement ligne par ligne
"contenu" comporte chaque caractère de la ligne lue à chaque tour de boucle
remplir la liste de paramètres "objet" avec les éléments qui sont dans "contenu"
instancier les objets 3D à l'aide de ces paramètres après les avoir convertis dans le bon format
*/

void Tas::LoadObjectFromFile(string fichierObjet){
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
				for(int i = 2; i < 11; i++){
					stringstream convert(objet[i]);
					convert >> convertedToFloat[i];
				}
			    path = objet[1];
				po = vec3(convertedToFloat[2], convertedToFloat[3], convertedToFloat[4]);
				sc = vec3(convertedToFloat[5], convertedToFloat[6], convertedToFloat[7]);
				ro = vec3(convertedToFloat[8], convertedToFloat[9], convertedToFloat[10]);
				if (listObjet.size() == 0)
				{	
					Objet3D newObjet(id,path, po, sc, ro);
    				objetBase = newObjet;
				}
			    Objet3D newObjet(id, po, sc, ro);
				listObjet.push_back(newObjet);
    		}
    		
    		
    	}
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier : " << fichierObjet << endl;
}

mat4 Tas::getModelMatrix(){
		mat4 modelMatrix  = mat4(1.0f);
        modelMatrix = translate(modelMatrix, position);

        modelMatrix = scale(modelMatrix, scaleTas);
        //Rotation commune à tous les éléments du tas.
        modelMatrix = rotate(modelMatrix, radians(angleRotation[0]), vec3(1,0,0));
        modelMatrix = rotate(modelMatrix, radians(angleRotation[1]), vec3(0,1,0));
        modelMatrix = rotate(modelMatrix, radians(angleRotation[2]), vec3(0,0,1));

        modelMatrix = translate(modelMatrix, objetBase.getposition()); 
        
        modelMatrix = scale(modelMatrix, objetBase.getscaleObject());

        //rotation propre à l'objet.
        vec3 angle = objetBase.getangleRotation();
        modelMatrix = rotate(modelMatrix, radians(angle[0]), vec3(1,0,0));
        modelMatrix = rotate(modelMatrix, radians(angle[1]), vec3(0,1,0));
        modelMatrix = rotate(modelMatrix, radians(angle[2]), vec3(0,0,1));

        return modelMatrix;
}

int Tas::getlistObjetSize(){
	return listObjet.size();
}

Objet3D Tas::getObjetBase(){
    return objetBase;
}

void Tas::Draw(Shader shader,float ZCam){
	//Draw the loaded model

   	glm::mat4 modelMatrix = glm::mat4(1.0f);

   	for (int i = 0; i < listObjet.size(); ++i)
   	{
   		ActionTas(id, objetBase.getEmplacement(),&listObjet[i]);
        objetBase.setPosition(listObjet[i].getposition());
   		objetBase.setScale(listObjet[i].getscaleObject());
   		objetBase.setRotation(listObjet[i].getangleRotation());
   		modelMatrix = getModelMatrix();
   		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        if (DrawCondition(modelMatrix[3][2], ZCam))
        objetBase.Draw(shader);
   	}
    
}

bool Tas::DrawCondition(int Zobj, float ZCam){
    float d;
    d = abs(ZCam) - abs(Zobj);
    if (d>5)
    {
        return false;
    }
     if (d<-40)
    {
        return false;
    }
    return true;
 }

vec3 Tas::getPositionTas(){
    return position;
}

int Tas::getIdTas(){
    return id;
}
float Tas::getZ(){
    return position[2];
}
void Tas::changeScene(){
    listObjet.clear();
    objetBase.changeScene();
}
