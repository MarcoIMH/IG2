#include "Rio.h"
#include "IG2ApplicationContext.h"

#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreViewport.h>
#include <OgreMeshManager.h>
#include <OgreTechnique.h>

#include <OgreRenderTarget.h>
#include <OgreRenderTexture.h>

#include <OgreTexture.h>
#include <OgreTextureUnitState.h>
#include <OgreTextureManager.h>


#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>
#include <OgrePass.h>

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>

Rio::Rio(SceneNode* mNode) : EntidadIG(mNode), _isWater(true) {
	_rio = new Plano(mNode, "PlanoAgua");
	_rio->setTexture("IG2/reflejo");

    setReflejo();

    appListeners.push_back(this);
}

Rio::~Rio()
{
    if(_mpRef != nullptr) delete _mpRef;
}

bool Rio::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_r) {        
        if (_isWater) {
            _rio->setTexture("Practica1/WaterWithStones");            
        }
        else{
            _rio->setTexture("IG2/reflejo");
        }
        _isWater = !_isWater;
    }
    return false;
}

void Rio::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
    sendEvent(FlipMessage());
}

void Rio::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
    sendEvent(UnFlipMessage());
}

void Rio::setReflejo()
{
    _mpRef = new MovablePlane(Vector3::UNIT_Y, 0);
    mNode->attachObject(_mpRef);

    _camRef = mSM->createCamera("RefCam");

    //Configuración frustum
    _camRef->setNearClipDistance(mSM->getCamera("Cam")->getNearClipDistance());
    _camRef->setFarClipDistance(mSM->getCamera("Cam")->getFarClipDistance());
    _camRef->setAutoAspectRatio(mSM->getCamera("Cam")->getAutoAspectRatio());
    mSM->getSceneNode("nCam")->attachObject(_camRef);

    _camRef->enableReflection(_mpRef);
    _camRef->enableCustomNearClipPlane(_mpRef);   

    TexturePtr rttRef = TextureManager::getSingleton().createManual(
        "rttReflejo",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        TEX_TYPE_2D, 
        (Real)mSM->getCamera("Cam")->getViewport()->getActualWidth(), // widht ejemplo
        (Real)mSM->getCamera("Cam")->getViewport()->getActualHeight(), // height ejemplo
        0, PF_R8G8B8, TU_RENDERTARGET);

    RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
    renderTexture->addListener(this);

    Viewport* vpt = renderTexture->addViewport(_camRef); 
    vpt->setClearEveryFrame(true); 
    //vpt->setBackgroundColour(ColourValue::…); // black/white

    TextureUnitState* tu = _rio->getEntity()->getSubEntity(0)->getMaterial()->
        getTechnique(0)->getPass(0)->
        createTextureUnitState("rttReflejo"); 

    tu->setColourOperation(LBO_ADD);
    tu->setProjectiveTexturing(true, _camRef);
}
