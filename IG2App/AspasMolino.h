#pragma once
#include "Aspa.h"

class IG2App;

using namespace Ogre;

class AspasMolino : public EntidadIG {
public:
	AspasMolino(int numAspas_, SceneNode* mNode);
	~AspasMolino();

	void giroAspasMolino(Ogre::Real grados = 3);
	void esconderCilindro();
protected:
	SceneNode* cilindroCentral;
	int numAspas;
	Aspa** arrayAspas;
	bool cilindroTransladado;
};

