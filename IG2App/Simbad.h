#pragma once
#include "EntidadIG.h"

class Simbad :	public EntidadIG{
public:
	Simbad(Ogre::SceneNode* mNode);
	~Simbad();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;  // InputListener
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
private:
	Entity* sinbad;
	Entity* sword;
	bool swordLeftHand;
	bool isExplosionTime;

	Ogre::AnimationState* as_Dance;
	Ogre::AnimationState* as_RunBase;
	Ogre::AnimationState* as_RunTop;
	Ogre::AnimationState* as_IdleTop;

	Ogre::Animation* animacionRuta;
	Ogre::AnimationState* as_RunPlaneCenter;
};

