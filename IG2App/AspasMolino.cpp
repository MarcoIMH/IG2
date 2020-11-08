#include "AspasMolino.h"
#include "IG2App.h"

AspasMolino::AspasMolino(int numAspas_, SceneNode *mNode) : 
    EntidadIG(mNode),
	numAspas(numAspas_),
    cilindroTransladado(false)
{
    arrayAspas = new Aspa * [numAspas];	

    cilindroCentral = mNode->createChildSceneNode();
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    ent->setMaterialName("Practica1/Metal");
    cilindroCentral->attachObject(ent);

    cilindroCentral->pitch(Ogre::Degree(90));
    cilindroCentral->scale(6, 4, 6);

    float ang = 360 / numAspas;
    for (int x = 0; x < numAspas; x++) {
        SceneNode* aspaNode = mNode->createChildSceneNode();

        arrayAspas[x] = new Aspa(aspaNode);

        aspaNode->setPosition(80 * Ogre::Math::Cos(Ogre::Degree(x * ang)),
            80 * Ogre::Math::Sin(Ogre::Degree(x * ang)), 0);

        aspaNode->roll(Ogre::Degree(x * ang));    
        arrayAspas[x]->getCilindroNode()->roll(Ogre::Degree(-x * ang));
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


void AspasMolino::giroAspasMolino(Ogre::Real grados)
{
    mNode->roll(Ogre::Degree(grados));

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

void AspasMolino::ocultaCilindros()
{
    for (int x = 0; x < numAspas; x++) {
        arrayAspas[x]->setAdornoVisible(false);
    }
}

void AspasMolino::muestraCilindros() {
    for (int x = 0; x < numAspas; x++) {
        arrayAspas[x]->setAdornoVisible(true);
    }
}

