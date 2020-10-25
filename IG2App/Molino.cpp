#include "Molino.h"

Molino::Molino(SceneManager* mSM)
{
	mNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
	aspasNode = mNode->createChildSceneNode("aspas");
	esferaNode = mNode->createChildSceneNode("techo");
	cilindroNode = mNode->createChildSceneNode("cuerpo");

	Entity* ent = mSM->createEntity("Barrel.mesh");
	cilindroNode->attachObject(ent);
	cilindroNode->setScale(28, 30, 28);
	cilindroNode->translate(0, -100, -80);

	ent = mSM->createEntity("sphere.mesh");
	esferaNode->attachObject(ent);
	esferaNode->setScale(0.8f, 0.8f, 0.8f);
	esferaNode->translate(0, 30, -80);

	aspas = new AspasMolino(6, aspasNode);
}

Molino::~Molino()
{
	delete aspas;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		aspas->giroAspasMolino();
	}
	return false;
}
