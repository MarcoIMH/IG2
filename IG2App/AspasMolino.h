#pragma once
#include "Aspa.h"

class IG2App;

using namespace Ogre;

class AspasMolino
{
public:
	AspasMolino(int numAspas_, IG2App* igApp, SceneNode* aspasNode);
	~AspasMolino();

	void giroAspasMolino();
protected:
	SceneNode* aspasNode;
	int numAspas;
	Aspa** arrayAspas;
};

