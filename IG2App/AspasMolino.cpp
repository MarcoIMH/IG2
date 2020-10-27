#include "AspasMolino.h"
#include "IG2App.h"

AspasMolino::AspasMolino(int numAspas_, SceneNode *_aspasNode) : 
    aspasNode(_aspasNode),
	numAspas(numAspas_),
    cilindroTransladado(false)
{
    arrayAspas = new Aspa * [numAspas];	

    cilindroCentral = aspasNode->createChildSceneNode();
    Ogre::Entity* ent = aspasNode->getCreator()->createEntity("Barrel.mesh");
    cilindroCentral->attachObject(ent);

    cilindroCentral->pitch(Ogre::Degree(90));
    cilindroCentral->scale(6, 4, 6);

    float ang = 360 / numAspas;
    for (int x = 0; x < numAspas; x++) {
        SceneNode* aspaNode = aspasNode->createChildSceneNode();
        SceneNode* tableroNode = aspaNode->createChildSceneNode();
        SceneNode* cilindroNode = aspaNode->createChildSceneNode();

        arrayAspas[x] = new Aspa(aspaNode, tableroNode, cilindroNode);

        aspaNode->setPosition(80 * Ogre::Math::Cos(Ogre::Degree(x * ang)),
            80 * Ogre::Math::Sin(Ogre::Degree(x * ang)), 0);

        aspaNode->roll(Ogre::Degree(x * ang));
        cilindroNode->roll(Ogre::Degree(-x * ang));
    }
}

AspasMolino::~AspasMolino()
{
    for (int x = 0; x < numAspas; x++)
    {
        delete arrayAspas[x];
        arrayAspas[x] = nullptr;
    }
    delete[] arrayAspas;
}


void AspasMolino::giroAspasMolino(int grados)
{
    aspasNode->roll(Ogre::Degree(grados));

    for (int x = 0; x < numAspas; x++) {
        arrayAspas[x]->giroAspa(grados);
    }
}

void AspasMolino::esconderCilindro()
{
    if (!cilindroTransladado) {
        cilindroCentral->translate(0, 0, -11);
        cilindroTransladado = true;
    }
}

