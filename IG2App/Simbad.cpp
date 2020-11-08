#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* mNode) :EntidadIG(mNode)
{
	Entity* sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);
}

Simbad::~Simbad()
{
}
