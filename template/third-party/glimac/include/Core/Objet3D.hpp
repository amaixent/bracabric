#pragma once

namespace glimac {

class Objet3D
{
private:
	int id;
	int nbTextures;
	
public:
	Objet3D();
	~Objet3D();

	void seDeplacer();
	void action();

	/* data */
};
}