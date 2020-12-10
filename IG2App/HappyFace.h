#pragma once
#include "EntidadIG.h"
class HappyFace : public EntidadIG
{
public:
	HappyFace(SceneNode* _mNode) : EntidadIG(_mNode) {
        happyFaceEntity = mSM->createEntity("sphere.mesh");
        happyFaceEntity->setMaterialName("Practica1/HappyFace");
        mNode->attachObject(happyFaceEntity);
        mNode->setScale(0.2f, 0.2f, 0.2f);
        mNode->translate(500, 20, -240);
        addListener(this);
	}

    virtual void receiveEvent(Messages msg) override {
        if(msg.message == MessageType::flipFace)
            happyFaceEntity->setMaterialName("Practica1/HappyFace_flip");
        if (msg.message == MessageType::unflipFace)
            happyFaceEntity->setMaterialName("Practica1/HappyFace");
    }
    
private:
    Entity* happyFaceEntity;
};

