#include "Simbad.h"
#include <iostream>


Simbad::Simbad(Ogre::SceneNode* mNode) :EntidadIG(mNode)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);

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

			as_RunBase->setEnabled(true);
			as_RunBase->setLoop(true);
		}
		else {
			as_RunBase->setEnabled(false);
			as_RunBase->setLoop(false);

			as_Dance->setEnabled(true);
			as_Dance->setLoop(true);			
		}
	}
	return false;
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if(as_Dance->getEnabled()) as_Dance->addTime(evt.timeSinceLastEvent);
	else if (as_RunBase->getEnabled()) as_RunBase->addTime(evt.timeSinceLastEvent);
	else if (as_RunTop->getEnabled()) as_RunTop->addTime(evt.timeSinceLastEvent);
}
