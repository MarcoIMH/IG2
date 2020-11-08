#pragma once
#include "EntidadIG.h"

class Aspa: public EntidadIG {
public:
	Aspa(Ogre::SceneNode * mNode);
	~Aspa() {};

	void giroAspa(Ogre::Real grados);
	inline Ogre::SceneNode* const getCilindroNode() { return cilindroNode; }
	void setAdornoTexture(std::string texture);
	void setAdornoVisible(bool v);
protected:
	Ogre::SceneNode* tableroNode;
	Ogre::SceneNode* cilindroNode;
	Entity* adorno;
};

