#include "EntidadIG.h"

std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(Ogre::SceneNode* node)
{
	//appListeners = std::vector<EntidadIG*>(0, nullptr);
	mNode = node;
	mSM = mNode->getCreator();
}

EntidadIG::~EntidadIG()
{
}

void EntidadIG::addListener(EntidadIG* entidad)
{
	appListeners.push_back(entidad);
}

void EntidadIG::sendEvent(EntidadIG* entidad)
{
	for (auto e : appListeners)
		e->receiveEvent(this);
		//e->receiveEvent(entidad);
}

bool EntidadIG::keyPressed(const OgreBites::KeyboardEvent& evnt)
{
	return false;
}
