#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>

class Aspa
{
public:
	Aspa(Ogre::SceneNode *aN, Ogre::SceneNode* tN, Ogre::SceneNode* cN);
	~Aspa() {};

	void giroAspa(int grados);
protected:
	Ogre::SceneNode* aspaNode;
	Ogre::SceneNode* tableroNode;
	Ogre::SceneNode* cilindroNode;
};

