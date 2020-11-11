#include "Boya.h"

Boya::Boya(SceneNode* mNode) : EntidadIG(mNode)
{
	boyaEntity = mSM->createEntity("Barrel.mesh");
	mNode->attachObject(boyaEntity);
	boyaEntity->setMaterialName("Practica1/Checker");
}
