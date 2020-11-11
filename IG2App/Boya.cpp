#include "Boya.h"

Boya::Boya(SceneNode* mNode) : EntidadIG(mNode)
{
	boyaEntity = mSM->createEntity("Barrel.mesh");
	mNode->attachObject(boyaEntity);
	boyaEntity->setMaterialName("Practica1/Checker");

	mNode->setScale(Vector3(10, 7, 10));
	mNode->setInitialState();

	Ogre::Real duracion = 16;
	animacionBoya = mSM->createAnimation("AnimVV", duracion);
	NodeAnimationTrack* track = animacionBoya->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	Vector3 keyFramePos(-10, 0, 100);
	Real durPaso = duracion / 4.0;

	Quaternion quat;
	Vector3 src = Vector3(0, 0, 1);

	TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);	//origen

	kf = track->createNodeKeyFrame(durPaso * 1);			//Arriba
	kf->setTranslate(keyFramePos + Vector3(0, 20, 0));
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1)));

	kf = track->createNodeKeyFrame(durPaso * 3);			//Abajo
	kf->setTranslate(keyFramePos + Vector3(0, -20, 0));
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));

	kf = track->createNodeKeyFrame(durPaso * 4);			//Origen

	animacionBoya->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);

	es_Vaiven = mSM->createAnimationState("AnimVV");
	es_Vaiven->setEnabled(true);
	es_Vaiven->setLoop(true);

	appListeners.push_back(this);
}

void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	if (es_Vaiven->getEnabled()) es_Vaiven->addTime(evt.timeSinceLastFrame);
}
