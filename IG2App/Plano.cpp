#include "Plano.h"
#include <OgreMeshManager.h>

Plano::Plano(Ogre::SceneNode* mNode, std::string nombre, float w, float h) : EntidadIG(mNode)
{
    MeshManager::getSingleton().createPlane(nombre,
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z);

    Entity* ent = mSM->createEntity(nombre);
    mNode->attachObject(ent);
}
