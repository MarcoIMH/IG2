#include "Avion.h"
#include <iostream>

Avion::Avion(SceneNode* mNode): EntidadIG(mNode)
{
	radioGiro = 2000;

	avion = mNode->createChildSceneNode();

	avion->translate(Vector3(-radioGiro, 0, 0), Ogre::Node::TS_LOCAL);

	cuerpoNode = avion->createChildSceneNode();
	alaINode = avion->createChildSceneNode();
	alaDNode = avion->createChildSceneNode();
	frenteNode = avion->createChildSceneNode();
	pilotoNode = avion->createChildSceneNode();

	Entity* ent = mSM->createEntity("sphere.mesh");
	cuerpoNode->attachObject(ent);
	ent = mSM->createEntity("cube.mesh");
	alaINode->attachObject(ent);
	ent = mSM->createEntity("cube.mesh");
	alaDNode->attachObject(ent);
	ent = mSM->createEntity("Barrel.mesh");
	frenteNode->attachObject(ent);
	ent = mSM->createEntity("ninja.mesh");
	pilotoNode->attachObject(ent);

	heliceDNode = avion->createChildSceneNode();
	heliceINode = avion->createChildSceneNode();

	aspaD = new AspasMolino(5, heliceDNode);
	aspaI = new AspasMolino(5, heliceINode);

	cuerpoNode->scale(Vector3(2, 2, 2));
	alaINode->scale(Vector3(5, 0.3f, 1.3f));
	alaINode->translate(Vector3(250, 0, 0));
	alaDNode->scale(Vector3(5, 0.3f, 1.3f));
	alaDNode->translate(Vector3(-250, 0, 0));
	frenteNode->scale(Vector3(16, 4, 16));
	frenteNode->pitch(Degree(90));
	frenteNode->translate(Vector3(0, 0, 210));
	pilotoNode->translate(0, 100, 0);
	pilotoNode->yaw(Degree(180));
	heliceDNode->translate(Vector3(350, 0, 70));
	heliceDNode->scale(Vector3(0.5f, 0.5f, 0.5f));
	heliceINode->translate(Vector3(-350, 0, 70));
	heliceINode->scale(Vector3(0.5f, 0.5f, 0.5f));

	appListeners.push_back(this);
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		aspaD->giroAspasMolino(-3);
		aspaI->giroAspasMolino(-3);
	}
	return false;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	mNode->yaw(Ogre::Degree(2));
}
