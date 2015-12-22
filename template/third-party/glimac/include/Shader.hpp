#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
#include <GL/glew.h> // Include glew to get all the required OpenGL headers

using namespace std;

class Shader
{
public:
  	// The program ID
	GLuint Program;
	// Constructor reads and builds the shader
	Shader();
	void loadShader(string vertexPath, string fragmentPath);
  	// Use the program
  	void Use();
};
  
