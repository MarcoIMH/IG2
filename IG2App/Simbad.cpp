#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* mNode) :EntidadIG(mNode), swordLeftHand(false), isScene7(true)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);

	sword = mSM->createEntity("Sword.mesh");	
	sinbad->attachObjectToBone("Handle.R", sword);

	as_Dance = sinbad->getAnimationState("Dance");
	as_RunBase = sinbad->getAnimationState("RunBase");
	as_RunTop = sinbad->getAnimationState("RunTop");


	if (isScene7) {
		Ogre::Real duracion = 10;
		Vector3 keyFramePosInicial(mNode->getPosition());
		Vector3 src(0, 0, 1);

		animacionRuta = mSM->createAnimation("Ruta", duracion);
		NodeAnimationTrack* track = animacionRuta->createNodeTrack(0);
		track->setAssociatedNode(mNode);
		
		//ROTAR SINBAD HACIA EL CENTRO - KEY FRAME 0
		TransformKeyFrame* kf = track->createNodeKeyFrame(0);		

		//KF1
		kf = track->createNodeKeyFrame((Real) 1.5 );
		kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));

		//CENTRO DEL RIO - KEY FRAME 2
		kf = track->createNodeKeyFrame((Real) 4.5);
		kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));
		kf->setTranslate(keyFramePosInicial + Vector3(350, 0, -250));


		//ROTAR SINBAD - KEY FRAME 3
		kf = track->createNodeKeyFrame((Real) 6.5);
		kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));
		kf->setTranslate(keyFramePosInicial + Vector3(350, 0, -250));


		kf = track->createNodeKeyFrame((Real)9.5);
		kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));

		//ORIGEN - KEY FRAME 4
		kf = track->createNodeKeyFrame((Real) 10);

		animacionRuta->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);

		//Activamos la animación de correr
		as_RunBase->setEnabled(true);
		as_RunBase->setLoop(true);

		as_RunTop->setEnabled(false);
		as_RunTop->setLoop(false);

		//Activamos la animación de ruta
		as_RunPlaneCenter = mSM->createAnimationState("Ruta");
		as_RunPlaneCenter->setEnabled(true);
		as_RunPlaneCenter->setLoop(true);
	}
	else {
			as_Dance->setEnabled(true);
	}

	appListeners.push_back(this);
}

Simbad::~Simbad()
{
	
}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if(evt.keysym.sym == SDLK_c && !isScene7) {
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
	else if (evt.keysym.sym == SDLK_e && !isScene7) {
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
		if (isScene7) as_RunPlaneCenter->addTime(evt.timeSinceLastFrame);
	}
}
