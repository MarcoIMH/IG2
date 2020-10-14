#include "AspasMolino.h"
#include "IG2App.h"

AspasMolino::AspasMolino(int numAspas_, SceneManager* sMG_, IG2App *igApp) :
	numAspas(numAspas_)
{
    arrayAspas = new Aspa * [numAspas];
	aspasNode = sMG_->getRootSceneNode()->createChildSceneNode("aspas");

    float ang = 360 / numAspas;
    for (int x = 0; x < numAspas; x++) {
        SceneNode* aspaNode = aspasNode->createChildSceneNode("aspa_" + std::to_string(x + 1));
        SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(x + 1));
        SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(x + 1));

        arrayAspas[x] = new Aspa(sMG_, aspaNode, tableroNode, cilindroNode);
        igApp->addInputListener(arrayAspas[x]);

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

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_g) {
        aspasNode->roll(Ogre::Degree(3));
  }
    return true;
}
