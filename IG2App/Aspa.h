#pragma once
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>


class Aspa
{
public:
	Aspa(Ogre::SceneManager* mSM, Ogre::SceneNode *aN, Ogre::SceneNode* tN, Ogre::SceneNode* cN);
	~Aspa() {};
protected:
	Ogre::SceneNode* aspaNode;
	Ogre::SceneNode* tableroNode;
	Ogre::SceneNode* cilindroNode;
};

