#pragma once
#include "Aspa.h"

class IG2App;

using namespace Ogre;

class AspasMolino : public OgreBites::InputListener
{
public:
	AspasMolino(int numAspas_, SceneManager* sMG_, IG2App* igApp);
	~AspasMolino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
protected:
	SceneNode* aspasNode;
	int numAspas;
	Aspa** arrayAspas;
};

