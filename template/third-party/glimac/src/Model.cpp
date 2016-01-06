#include <Model.hpp>



void Model::Draw(Shader shader)
{
    for(GLuint i = 0; i < this->meshes.size(); i++)
        this->meshes[i].Draw(shader);
} 

void Model::loadModel(string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));

    this->processNode(scene->mRootNode, scene);
} 

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process all the node's meshes (if any)
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
        this->meshes.push_back(this->processMesh(mesh, scene));			
    }
    // Then do the same for each of its children
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }
} 

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // Process vertex positions, normals and texture coordinates
        glm::vec3 vector; 
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z; 
		vertex.Position = vector;
        
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector; 

		if(mesh->mTextureCoords[0])// contain texture coordinates 
		{
		    glm::vec2 vec;
		    vec.x = mesh->mTextureCoords[0][i].x; 
		    vec.y = mesh->mTextureCoords[0][i].y;
		    vertex.TexCoords = vec;
		}
		else{
		    vertex.TexCoords = glm::vec2(0.0f, 0.0f);  
		}

        vertices.push_back(vertex);
    }
    // Process indices
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
	{
	    aiFace face = mesh->mFaces[i];
	    for(GLuint j = 0; j < face.mNumIndices; j++)
	        indices.push_back(face.mIndices[j]);
	}  
    // Process material
	if(mesh->mMaterialIndex >= 0)
    { 
	    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	    vector<Texture> diffuseMaps = this->loadMaterialTextures(material, 
	                                        aiTextureType_DIFFUSE, "texture_diffuse");
	    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	    vector<Texture> specularMaps = this->loadMaterialTextures(material, 
	                                        aiTextureType_SPECULAR, "texture_specular");
	    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	} 

    return Mesh(vertices, indices, textures);
} 

GLint Model::TextureFromFile(const char* path, string directory)
{
     //Generate texture ID and load texture data 

    string filename = string(path);
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    unique_ptr<glimac::Image> image = glimac::loadImage(filename.c_str());
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);    

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    //SOIL_free_image_data(image);
    return textureID;
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    vector<Texture> textures_loaded;
   
    if (strncmp (&directory[19],"2",1) == 0)
    {
      
        Texture texture;

        texture.id = TextureFromFile("texture.jpg" , this->directory);
        texture.type = typeName;
        texture.path = directory + "texture.jpg";
        textures.push_back(texture);

        this->textures_loaded.push_back(texture); 

    }
    else{
        for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
        {   
            aiString str;
            mat->GetTexture(type, i, &str);
            GLboolean skip = false;

            for(GLuint j = 0; j < textures_loaded.size(); j++)
            {
                if(textures_loaded[j].path == str)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; 
                    break;
                }
            }

            if(!skip)
            {   // Performance improvement : If texture hasn't been loaded already, load it
                Texture texture;

                texture.id = TextureFromFile(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str;
                textures.push_back(texture);

                this->textures_loaded.push_back(texture);  // Add to loaded textures
            }
        }

    }
    return textures;
}
void Model::changeScene(){
    for (int i = 0; i < meshes.size(); ++i)
    {
        meshes[i].changeScene();
    }
}
