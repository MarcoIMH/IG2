#pragma once
#include "AspasMolino.h"
#include <OgreParticleSystem.h>

using namespace Ogre;

class Avion : public EntidadIG {
public:
	Avion(SceneNode *mNode);
	~Avion() {
		delete aspaD;
		delete aspaI;
	}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;  // InputListener
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
private:
	SceneNode* cuerpoNode;
	SceneNode* alaINode;
	SceneNode* alaDNode;
	SceneNode* frenteNode;
	SceneNode* pilotoNode;
	SceneNode* heliceINode;
	SceneNode* heliceDNode;

	AspasMolino* aspaI;
	AspasMolino* aspaD;

	Light* luz;

	ParticleSystem* pSysAvion;
	SceneNode* psysNode;

	int radioGiro;
	bool r_event = false;
};

