#pragma once
#include "EntidadIG.h"
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

class Boya : public EntidadIG
{
public:
	Boya(SceneNode* mNode);

	void frameRendered(const Ogre::FrameEvent& evt) override;
private:
	Entity* boyaEntity;
	Ogre::Animation* animacionBoya;
	Ogre::AnimationState* es_Vaiven;
};

