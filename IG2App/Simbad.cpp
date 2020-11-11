#include "Simbad.h"
#include <iostream>


Simbad::Simbad(Ogre::SceneNode* mNode) :EntidadIG(mNode), swordLeftHand(false)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);

	sword = mSM->createEntity("Sword.mesh");	
	sinbad->attachObjectToBone("Handle.R", sword);

	as_Dance = sinbad->getAnimationState("Dance");
	as_Dance->setEnabled(true);
	as_Dance->setLoop(true);

	as_RunBase = sinbad->getAnimationState("RunBase");
	as_RunBase->setEnabled(false);
	as_RunBase->setLoop(false);

	as_RunTop = sinbad->getAnimationState("RunTop");
	as_RunTop->setEnabled(false);
	as_RunTop->setLoop(false);

	appListeners.push_back(this);
}

Simbad::~Simbad()
{

}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if(evt.keysym.sym == SDLK_c) {
		if (as_Dance->getEnabled()) {
			as_Dance->setEnabled(false);
			as_Dance->setLoop(false);
			as_Dance->setTimePosition(0);

			as_RunBase->setEnabled(true);
			as_RunBase->setLoop(true);

			as_RunTop->setEnabled(true);
			as_RunTop->setLoop(true);
		}
		else {
			as_RunBase->setEnabled(false);
			as_RunBase->setLoop(false);
			as_RunBase->setTimePosition(0);

			as_RunTop->setEnabled(false);
			as_RunTop->setLoop(false);
			as_RunTop->setTimePosition(0);

			as_Dance->setEnabled(true);
			as_Dance->setLoop(true);	
		}
	}
	else if (evt.keysym.sym == SDLK_e) {
		if (swordLeftHand) {
			sinbad->detachObjectFromBone(sword);
			sinbad->attachObjectToBone("Handle.R", sword);			
		}			
		else {
			sinbad->detachObjectFromBone(sword);
			sinbad->attachObjectToBone("Handle.L", sword);
		}
		swordLeftHand = !swordLeftHand;
	}
	return false;
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (as_Dance->getEnabled()) as_Dance->addTime(evt.timeSinceLastFrame);
	else {
		as_RunBase->addTime(evt.timeSinceLastFrame);
		as_RunTop->addTime(evt.timeSinceLastFrame);
	}
}
