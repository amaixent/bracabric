#version 330 core


in vec3 Position_vs;
in vec3 Normal_vs;
in vec2 TexCoords_vs;  

out vec4 color;

 uniform vec3 uKd;
 uniform vec3 uKs;
 uniform float uShininess;
 uniform vec3 uLightDir_vs;
 uniform vec3 uLightIntensity;


uniform sampler2D texture_diffuse1;

 vec3 blinnPhong(){
 	vec3 couleur, halfVector;
 	halfVector = normalize((normalize(-Position_vs)+normalize(uLightDir_vs))/2);
		//Li(Kd(wi˙N)+Ks(halfVector˙N)shininess)

 	couleur = uLightIntensity*(uKd*(max(dot(normalize(uLightDir_vs),normalize(Normal_vs)),0))
 		+ uKs*pow(max(dot(halfVector,normalize(Normal_vs)),0),uShininess));
 	//return vec3(1,1,1);
 	return couleur;
 }

 vec4 aura(){

 	float distance =  sqrt((Position_vs[0])*(Position_vs[0]) + (Position_vs[1])*(Position_vs[1]));
 	return vec4(5/distance,5/distance,5/distance,1);
 	
 }

void main() {

	color = vec4(texture(texture_diffuse1, TexCoords_vs))*vec4(blinnPhong(),1)*aura();

}