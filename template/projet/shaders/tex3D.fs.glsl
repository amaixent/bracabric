#version 330 core

in vec2 TexCoords;

out vec3 fFragColor;

uniform int uTexture;

void main()
{    
    fFragColor=texture(uTexture,TexCoords).xyz;
}