#version 330 core
layout (location = 0) in vec3 position;

out vec3 Position_vs;
out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;


void main()
{
    gl_Position =   projection * view * vec4(position, 1.0);  
    TexCoords = position;
    Position_vs = vec3(gl_Position);
}  
