#pragma once
#include "Aspa.h"

class IG2App;

using namespace Ogre;

class AspasMolino
{
public:
	AspasMolino(int numAspas_, SceneNode* aspasNode);
	~AspasMolino();

	void giroAspasMolino(int grados = 3);
	void esconderCilindro();
protected:
	SceneNode* aspasNode;
	SceneNode* cilindroCentral;
	int numAspas;
	Aspa** arrayAspas;
	bool cilindroTransladado;
};

