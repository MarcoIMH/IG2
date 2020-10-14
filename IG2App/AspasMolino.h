#pragma once
#include "Aspa.h"

using namespace Ogre;

class AspasMolino : public OgreBites::InputListener
{
public:
	AspasMolino(int numAspas_, SceneManager* sMG_);
	~AspasMolino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
protected:
	SceneNode* aspasNode;
	int numAspas;
	Aspa** arrayAspas;
};

