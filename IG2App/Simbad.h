#pragma once
#include "EntidadIG.h"

class Simbad :	public EntidadIG{
public:
	Simbad(Ogre::SceneNode* mNode);
	~Simbad();
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
private:
	Entity* sinbad;
	Ogre::AnimationState* as_Dance;
	Ogre::AnimationState* as_RunBase;
	Ogre::AnimationState* as_RunTop;
};

