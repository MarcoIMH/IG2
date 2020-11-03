#pragma once
#include "EntidadIG.h"
class Plano :public EntidadIG {
public:
	Plano(Ogre::SceneNode* mNode, std::string nombre, float w = 1080.0f, float h = 800.0f);
	~Plano() {};
};

