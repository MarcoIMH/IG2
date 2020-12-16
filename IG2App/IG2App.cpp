#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>
#include "Simbad.h"
#include "Boya.h"
#include "Rio.h"
#include "HappyFace.h"
#include <OgreCompositor.h>
#include <OgreCompositorChain.h>
#include <OgreCompositionPass.h>
#include <OgreCompositorInstance.h>
#include <OgreCompositorManager.h>
#include <OgreCompositorLogic.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_l) {
        isLuminance = !isLuminance;
        CompositorManager::getSingleton().setCompositorEnabled(mSM->getCamera("Cam")->getViewport(), "IG2/Luminance", isLuminance);       
    }
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;

  for (auto e : sceneObjects) {
      delete e;
      e = nullptr;
  }
  sceneObjects.clear();

  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));    //Scene background color
  CompositorManager::getSingleton().addCompositor(vp, "IG2/Luminance");

  //------------------------------------------------------------------------

  // without light we would just get a black screen   

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(1.0, 1.0, 1.0);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();

  //------------------------------------------------------------------------

  // finally something to render

  setScene(1);
  switch (sceneId) {
  case 1: scene1(); break;  // Practica 2.0
  }

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);
  //------------------------------------------------------------------------
  for (EntidadIG* entity : EntidadIG::appListeners) {
      addInputListener(entity);
  }
}

void IG2App::scene1()
{
    //SKYPLANE
    mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -50), "IG2/spaceGLSL", 1, 1, true, 1.0, 10, 10);
    //mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200), "IG2App/space", 1, 1, true, 0.0, 10, 10);

    //AGUA
    SceneNode* planoAguaNode = mSM->getRootSceneNode()->createChildSceneNode("PlanoAguaNode");
    Rio* water = new Rio(planoAguaNode);
    sceneObjects.push_back(water);   

    //MOLINO Y SU PLANO
    SceneNode* molinoNode = mSM->getRootSceneNode()->createChildSceneNode();
    Molino* molino = new Molino(molinoNode);
    sceneObjects.push_back(molino);
    //Transformaciones molino
    molinoNode->translate(450, 190, -240);

    SceneNode* planoMolinoNode = mSM->getRootSceneNode()->createChildSceneNode();
    Plano* pM = new Plano(planoMolinoNode, "PlanoMolino");
    pM->setTexture("Practica1/Orange");
    sceneObjects.push_back(pM);
    //Transformaciones plano molino
    planoMolinoNode->scale(0.2f, 1.0f, 0.3f);
    planoMolinoNode->translate(430, 1, -280);

    //SINBAD
    SceneNode* sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
    Simbad* sinbad = new Simbad(sinbadNode);
    sceneObjects.push_back(sinbad);

    //Transformaciones sinbad
    sinbadNode->setScale(8, 8, 8);
    sinbadNode->translate(-300, 40, 200);
    sinbadNode->setInitialState();

    ////AVION
    SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode();
    Avion* avion = new Avion(avionNode);
    sceneObjects.push_back(avion);
    //Transformaciones AVion
    avionNode->setScale(0.1f, 0.1f, 0.1f);
    avionNode->translate(0, 400, 0);

    //BOYA
    SceneNode* boyaNode = mSM->getRootSceneNode()->createChildSceneNode();
    Boya* boya = new Boya(boyaNode);
    boyaNode->scale(Vector3(0.5, 0.5, 0.5));
    boyaNode->setInitialState();
    sceneObjects.push_back(boya);

    ////HAPPY FACE
    SceneNode* faceNode = mSM->getRootSceneNode()->createChildSceneNode();
    HappyFace* happyFace = new HappyFace(faceNode);
}   
//------------------------------------------------------------------------