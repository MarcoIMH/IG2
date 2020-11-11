#include "Molino.h"

Molino::Molino(SceneNode *mNode): EntidadIG(mNode)
{
	nodoFicticioCentro = mNode->createChildSceneNode();
	//aspasNode = nodoFicticioCentro->createChildSceneNode("aspas");	//ficticio
	aspasNode = mNode->createChildSceneNode("aspas");	//(truco)
	esferaNode = mNode->createChildSceneNode("techo");
	cilindroNode = mNode->createChildSceneNode("cuerpo");

	nodoFicticioCentro->translate(0, 30, -80);
	//aspasNode->translate(0, 0, 80);

	Entity* ent = mSM->createEntity("Barrel.mesh"); //CUERPO DEL MOLINO
	ent->setMaterialName("Practica1/Floor"); 
	cilindroNode->attachObject(ent);
	cilindroNode->setScale(28, 30, 28);
	cilindroNode->translate(0, -100, -80);

	cupula = mSM->createEntity("sphere.mesh");		//PARTE SUPERIOR ESFÉRICA DEL MOLINO
	cupula->setMaterialName("Practica1/Yellow");
	esferaNode->attachObject(cupula);
	esferaNode->setScale(0.8f, 0.8f, 0.8f);
	esferaNode->translate(0, 30, -80);

	aspas = new AspasMolino(6, aspasNode);
	aspasNode->translate(0, 30, 0);

	appListeners.push_back(this);
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
	if (evt.keysym.sym == SDLK_c) {
		aspas->esconderCilindro();
	}
	if (evt.keysym.sym == SDLK_h) {
		//Nodo ficticio
		//nodoFicticioCentro->yaw(Ogre::Degree(3));

		//Truco
		Ogre::Real radius = esferaNode->convertLocalToWorldPosition(Vector3(0, 0, 0)).distance(aspasNode->convertLocalToWorldPosition(Vector3(0, 0, 0)));
		aspasNode->setPosition(0, 0, 0);
		aspasNode->yaw(Ogre::Degree(3), Node::TS_WORLD);
		aspasNode->translate(0, 0, radius, Node::TS_LOCAL);
		aspasNode->translate(esferaNode->convertLocalToWorldPosition(Vector3(0, 0, 0)), Node::TS_WORLD);
	}
	if (evt.keysym.sym == SDLK_r) {
		if (!r_event) {
			cupula->setMaterialName("Practica1/Red");		
			aspas->ocultaCilindros();
		}
		else {
			cupula->setMaterialName("Practica1/Yellow");
			aspas->muestraCilindros();
		}
		r_event = !r_event;
	}
	return false;
}

void Molino::frameRendered(const Ogre::FrameEvent& evnt)
{
	Ogre::Real time = evnt.timeSinceLastFrame;		
	aspas->giroAspasMolino(time * 8);
}
