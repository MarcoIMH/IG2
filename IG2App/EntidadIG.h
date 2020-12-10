#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>
#include <vector>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include "Messages.h"

using namespace Ogre;

class EntidadIG: public OgreBites::InputListener
{
public:
	EntidadIG(Ogre::SceneNode* node);
	~EntidadIG();

	static std::vector<EntidadIG*> appListeners;
	static void addListener(EntidadIG* entidad);

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	void sendEvent(EntidadIG* entidad);
	void sendEvent(Messages mensaje);
	virtual void receiveEvent(EntidadIG* entidad) {};
	virtual void receiveEvent(Messages mensaje) {};

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evnt);

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;	
};

