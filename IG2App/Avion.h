#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>

#include "AspasMolino.h"

using namespace Ogre;

class Avion : public OgreBites::InputListener
{
public:
	Avion(SceneManager* mSM);
	~Avion() {
		delete aspaD;
		delete aspaI;
	}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
private:
	SceneNode* mNode;
	SceneNode* cuerpoNode;
	SceneNode* alaINode;
	SceneNode* alaDNode;
	SceneNode* frenteNode;
	SceneNode* pilotoNode;
	SceneNode* heliceINode;
	SceneNode* heliceDNode;

	AspasMolino* aspaI;
	AspasMolino* aspaD;
};

