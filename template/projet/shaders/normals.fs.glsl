#version 330 core


in vec3 Position_vs;
in vec3 Normal_vs;
in vec2 TexCoords_vs;  

out vec4 color;

uniform int uIdTas;


void main() {
	vec3 newNormalColor = Normal_vs*vec3(cos(uIdTas),sin(uIdTas),1);
	color = vec4(newNormalColor,1);
	//color = vec4(1,1,1,1);
}