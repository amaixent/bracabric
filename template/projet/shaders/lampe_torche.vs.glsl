#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
// Sorties du shader
out vec3 Position_vs; // Position du sommet transformé dans l'espace View
out vec3 Normal_vs; // Normale du sommet transformé dans l'espace View
out vec2 TexCoords_vs; // Coordonnées de texture du sommet


void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords_vs = texCoords;
    Position_vs = vec3(gl_Position);
    Normal_vs = vec3(transpose(inverse(view*model)) * vec4(normal,0));
}