#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* aN, Ogre::SceneNode* tN, Ogre::SceneNode* cN):
    aspaNode(aN), tableroNode(tN), cilindroNode(cN)
{ 
    Ogre::SceneManager* mSM = aN->getCreator();

    Ogre::Entity* ent = mSM->createEntity("cube.mesh");
    tableroNode->attachObject(ent);
    tableroNode->setScale(1.6f, 0.4f, 0.02f);

    ent = mSM->createEntity("Barrel.mesh");
    cilindroNode->attachObject(ent);
    cilindroNode->translate(60, 0, 5);
    cilindroNode->setScale(1.5f, 4.0f, 1.5f);
}

void Aspa::giroAspa(int grados)
{
    cilindroNode->roll(Ogre::Degree(-grados));
}

