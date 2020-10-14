#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>

class Aspa : public OgreBites::InputListener
{
public:
	Aspa(Ogre::SceneManager* mSM, Ogre::SceneNode *aN, Ogre::SceneNode* tN, Ogre::SceneNode* cN);
	~Aspa() {};

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
protected:
	Ogre::SceneNode* aspaNode;
	Ogre::SceneNode* tableroNode;
	Ogre::SceneNode* cilindroNode;
};

