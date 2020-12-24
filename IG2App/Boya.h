#pragma once
#include "EntidadIG.h"

class Boya : public EntidadIG
{
public:
	Boya(SceneNode* mNode);

	void frameRendered(const Ogre::FrameEvent& evt) override;
	bool keyPressed(const OgreBites::KeyboardEvent& evnt) override;
private:
	Entity* boyaEntity;
	Ogre::Animation* animacionBoya;
	Ogre::AnimationState* es_Vaiven;

	bool explotaGS;
};

