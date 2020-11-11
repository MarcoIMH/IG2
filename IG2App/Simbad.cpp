#include "Simbad.h"
#include <iostream>


Simbad::Simbad(Ogre::SceneNode* mNode) :EntidadIG(mNode)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);

	as_Dance = sinbad->getAnimationState("Dance");
	as_Dance->setEnabled(false);
	as_Dance->setLoop(false);

	as_RunBase = sinbad->getAnimationState("RunBase");
	as_RunBase->setEnabled(false);
	as_RunBase->setLoop(false);

	as_RunTop = sinbad->getAnimationState("RunTop");
	as_RunTop->setEnabled(true);
	as_RunTop->setLoop(true);

	appListeners.push_back(this);
}

Simbad::~Simbad()
{

}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if(as_Dance->getEnabled()) as_Dance->addTime(evt.timeSinceLastEvent);
	else if (as_RunBase->getEnabled()) as_RunBase->addTime(evt.timeSinceLastEvent);
	else if (as_RunTop->getEnabled()) as_RunTop->addTime(evt.timeSinceLastEvent);
}
