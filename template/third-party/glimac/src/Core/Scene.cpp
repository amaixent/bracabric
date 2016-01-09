#include "Core/Scene.hpp"


namespace glimac {
    Scene::Scene(){}
    Scene::Scene(int identifiant,string fichierVs, string fichierFs, string fichierTas){
        shader.loadShader(fichierVs, fichierFs);
        LoadTasFromFile(fichierTas);
        id = identifiant;
        idTrajectoire = 0;
    }

    Scene::Scene(int identifiant,string fichierVs, string fichierFs, string fichierTas, string fichierSkybox){
        shader.loadShader(fichierVs, fichierFs);
        LoadTasFromFile(fichierTas);
        id = identifiant;
        idTrajectoire = 0;
        mySkybox.loadSkybox(identifiant, fichierSkybox); 
    }

    Scene::~Scene(){
    }

void Scene::changeScene(){
        
    this->mySkybox.changeSkybox();
     for (int i = 0; i < tabTas.size(); ++i)
    {    
        if(tabTas[i].getlistObjetSize()!= 0){
            tabTas[i].changeScene();
        }
    }
    tabTas.clear();
}

void Scene::chargeScene(int identifiant, string fichierVs,string fichierFs,string fichierTas,string fichierSkybox){
    changeScene();
    shader.loadShader(fichierVs, fichierFs);
    LoadTasFromFile(fichierTas);
    id = identifiant;
    idTrajectoire = 0;
    mySkybox.loadSkybox(identifiant, fichierSkybox);

}   

void Scene::LoadTasFromFile(string fichierTas){
    ifstream fichier(fichierTas);

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
                Tas newTas(id, path, po, sc, ro);
                tabTas.push_back(newTas);
            }
        }
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier : " << fichierTas << endl;

}

void Scene::Draw(TrackballCamera camera, GLuint screenWidth, GLuint screenHeight){

    mySkybox.Draw(camera,screenWidth,screenHeight, id);

    shader.Use();   // <-- Don't forget this one!
        
    // Transformation matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);/*aiMemoryInfo::cameras.Zoom*/
    glm::mat4 view = camera.getViewMatrix();//aiMemoryInfo::cameras.GetViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    //Blin Phong lampe_torche.fs.glsl
    glUniform1f(glGetUniformLocation(shader.Program , "uShininess"),2.0);
    glUniform3f(glGetUniformLocation(shader.Program , "uKd"), 1.0,1.0,1.0);
    glUniform3f(glGetUniformLocation(shader.Program , "uKs"), 1.0,1.0,1.0);
    vec4 temp =  view*vec4(1.0,1.0,1.0,0.0);
    glUniform3f(glGetUniformLocation(shader.Program , "uLightDir_vs"),temp[0],temp[1],temp[2]);
    vec4 temp2 = view*vec4(1.0,1.0,1.0,1.0);
    glUniform3f(glGetUniformLocation(shader.Program , "uLightPos_vs"),temp2[0],temp2[1],temp2[2]);
    glUniform3f(glGetUniformLocation(shader.Program , "uLightIntensity"), 1.5,1.5,1.5);


    //glUniform3f(glGetUniformLocation(shader.Program , "ucolorObjet"), 1.0,1.0,1.0);
    
    for (int i = 0; i < tabTas.size(); ++i)
    {   
        if(tabTas[i].getlistObjetSize()!= 0){
            tabTas[i].Draw(shader);
            // Scène 1 : color_position.fs.glsl
            vec3 temp3 = tabTas[i].getPositionTas();
            glUniform1f(glGetUniformLocation(shader.Program , "uIdTas"), tabTas[i].getIdTas());
        }
            
    }
}
int Scene::getId(){
    return id;
}
}

