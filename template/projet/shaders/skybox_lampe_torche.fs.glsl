#version 330 core
in vec3 TexCoords;

in vec3 Position_vs;

out vec4 color;


uniform samplerCube skybox;
 vec4 aura(){

 	float distance =  sqrt((Position_vs[0])*(Position_vs[0]) + (Position_vs[1])*(Position_vs[1]));
 	if (10/distance<1)
 	{
 		return vec4(10/distance,10/distance,10/distance,1);
 	}

 	else{
 		return vec4(1.0,1.0,1.0,1);
 	}
 	
 	
 }

void main()
{    
	//color = vec4(Position_vs,1);
    color = texture(skybox, TexCoords)*aura();
}