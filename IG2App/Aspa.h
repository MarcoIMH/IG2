#pragma once
#include "EntidadIG.h"

class Aspa: public EntidadIG {
public:
	Aspa(Ogre::SceneNode * mNode);
	~Aspa() {};

	void giroAspa(int grados);
	inline Ogre::SceneNode* const getCilindroNode() { return cilindroNode; }
protected:
	Ogre::SceneNode* tableroNode;
	Ogre::SceneNode* cilindroNode;
};

