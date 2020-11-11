#include "Simbad.h"
#include <iostream>


Simbad::Simbad(Ogre::SceneNode* mNode) :EntidadIG(mNode)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);
	as_Dance = sinbad->getAnimationState("Dance");
	as_Dance->setEnabled(true);
	as_Dance->setLoop(true);

	appListeners.push_back(this);
}

Simbad::~Simbad()
{

}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if(as_Dance->getEnabled()) as_Dance->addTime(evt.timeSinceLastEvent);
}
