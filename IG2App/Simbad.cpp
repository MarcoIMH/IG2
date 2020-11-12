#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* mNode) :EntidadIG(mNode), swordLeftHand(false)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);

	sword = mSM->createEntity("Sword.mesh");	
	sinbad->attachObjectToBone("Handle.R", sword);

	as_Dance = sinbad->getAnimationState("Dance");
	as_RunBase = sinbad->getAnimationState("RunBase");
	as_RunTop = sinbad->getAnimationState("RunTop");
		
	Ogre::Real duracion = 10;
	Vector3 keyFramePosInicial(mNode->getPosition());
	Vector3 src(0, 0, 1);

	animacionRuta = mSM->createAnimation("Ruta", duracion);
	NodeAnimationTrack* track = animacionRuta->createNodeTrack(0);
	track->setAssociatedNode(mNode);
		
	//SINBAD EN EL CENTRO MIRANDO A LA CÁMARA- KEY FRAME 0
	TransformKeyFrame* kf = track->createNodeKeyFrame(0);		

	//SINBAD ROTA HACIA EL CENTRO DEL RIO - KEY FRAME 1
	kf = track->createNodeKeyFrame((Real) 1.5 );
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));

	//SINBAD SE MUEVE HACIA EL CENTRO DEL RIO - KEY FRAME 2
	kf = track->createNodeKeyFrame((Real) 4.5);
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));
	kf->setTranslate(keyFramePosInicial + Vector3(350, 0, -250));

	//SINBAD ROTA HACIA EL CENTRO DEL PLANO - KEY FRAME 3
	kf = track->createNodeKeyFrame((Real) 6.5);
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));
	kf->setTranslate(keyFramePosInicial + Vector3(350, 0, -250));

	//SINBAD SE DESPLAZA AL CENTRO DEL PLANO - KEY FRAME4
	kf = track->createNodeKeyFrame((Real)9.5);
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));

	//SINBAD VUELVE A MIRAR HACIA LA CÁMARA EN EL CENTRO DEL PLANO - KEY FRAME 5
	kf = track->createNodeKeyFrame((Real) 10);

	animacionRuta->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);

	//Desactivamos la animación de bailar
	as_Dance->setEnabled(false);

	//Activamos la animación de correr
	as_RunBase->setEnabled(true);
	as_RunBase->setLoop(true);

	as_RunTop->setEnabled(true);
	as_RunTop->setLoop(true);

	//Activamos la animación de ruta
	as_RunPlaneCenter = mSM->createAnimationState("Ruta");
	as_RunPlaneCenter->setEnabled(true);
	as_RunPlaneCenter->setLoop(true);

	appListeners.push_back(this);
}

Simbad::~Simbad()
{
	
}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if(evt.keysym.sym == SDLK_c) {
		if (as_Dance->getEnabled()) {
			//Desactivar y resetear animación baile
			as_Dance->setEnabled(false);
			as_Dance->setTimePosition(0);

			//Se activa las animaciones  de correr y vaivén
			as_RunBase->setEnabled(true);
			as_RunTop->setEnabled(true);
			as_RunPlaneCenter->setEnabled(true);
		}
		else {
			//Parar las animaciones de correr y vaivén, resetear solo las de correr
			as_RunBase->setEnabled(false);
			as_RunTop->setEnabled(false);
			as_RunPlaneCenter->setEnabled(false);

			as_RunBase->setTimePosition(0);			
			as_RunTop->setTimePosition(0);
						
			//Activar la animación de bailar
			as_Dance->setEnabled(true);
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
		as_RunPlaneCenter->addTime(evt.timeSinceLastFrame);
	}
}
