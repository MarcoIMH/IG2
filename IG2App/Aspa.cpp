#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* mNode): EntidadIG(mNode)
{ 
    tableroNode = mNode->createChildSceneNode();
    cilindroNode = mNode->createChildSceneNode();

    Ogre::Entity* ent = mSM->createEntity("cube.mesh");
    ent->setMaterialName("Practica1/Brown");
    tableroNode->attachObject(ent);
    tableroNode->setScale(1.6f, 0.4f, 0.02f);

    adorno = mSM->createEntity("Barrel.mesh");
    adorno->setMaterialName("Practica1/Fucsia");
    cilindroNode->attachObject(adorno);
    cilindroNode->translate(60, 0, 5);
    cilindroNode->setScale(1.5f, 4.0f, 1.5f);
}

void Aspa::giroAspa(Ogre::Real grados)
{
    cilindroNode->roll(Ogre::Degree(-grados));
}

void Aspa::setAdornoTexture(std::string texture)
{
    adorno->setMaterialName(texture);
}

void Aspa::setAdornoVisible(bool v)
{
    adorno->setVisible(v);
}

