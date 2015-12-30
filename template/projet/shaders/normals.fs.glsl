#version 330 core


in vec3 Position_vs;
in vec3 Normal_vs;
in vec2 TexCoords_vs;  

out vec4 color;


void main() {

	color = vec4(Normal_vs,1);
	//color = vec4(1,1,1,1);
}