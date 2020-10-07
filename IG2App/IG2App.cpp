#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_g) {
      if (mSM->getSceneNode("clock") != nullptr) {
          mSM->getSceneNode("clock")->roll(Ogre::Degree(3));    //Rota reloj
      }
  }
  //else if (evt.keysym.sym == SDLK_???)
  
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
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
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));    //Scene background color

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //mLightNode->setDirection(Ogre::Vector3(0, 1, 0));  //vec3.normalise();
  //mLightNode->setDirection(Ogre::Vector3(0, -1, 0));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  //Ogre::Entity* ent = mSM->createEntity("Sword.mesh");  
  //Ogre::Entity* ent = mSM->createEntity("DamagedHelmet.mesh");
  //Ogre::Entity* ent = mSM->createEntity("ogrehead.mesh");    

  //mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------
  setScene(1);
  switch (sceneId) {
  case 0: scene0(); break;
  case 1: scene1(); break;
  case 2: scene2(); break;
  }
}
//------------------------------------------------------------------------
void IG2App::scene0() //Ejercicio 14
{
    //ROMAN BATHROOM
    Ogre::Entity* bathFloor = mSM->createEntity("RomanBathLower.mesh");
    Ogre::Entity* bathUpper = mSM->createEntity("RomanBathUpper.mesh");
    Ogre::Entity* columns = mSM->createEntity("Columns.mesh");

    Ogre::SceneNode* bathNode = mSM->getRootSceneNode()->createChildSceneNode("bath");
    bathNode->createChildSceneNode("bathUpper")->attachObject(bathUpper);
    bathNode->createChildSceneNode("bathFloor")->attachObject(bathFloor);
    bathNode->createChildSceneNode("columns")->attachObject(columns);

    bathNode->setScale(0.1f, 0.1f, 0.1f);

    //DRAGON
    Ogre::Entity* dragon = mSM->createEntity("dragon.mesh");
    Ogre::SceneNode* dragonNode = mSM->getRootSceneNode()->createChildSceneNode("dragon");
    dragonNode->attachObject(dragon);
    dragonNode->setScale(0.1f, 0.1f, 0.1f);
    dragonNode->setPosition(0, 10, 0);


    //SINBAD
    Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(ent);
    mSinbadNode->setScale(2, 2, 2);
    mSinbadNode->setPosition(0, 2, 0);
}
//------------------------------------------------------------------------
void IG2App::scene1()   //Ejercicio15
{   
    std::vector<SceneNode*> sphereVector;

    
    Ogre::SceneNode* clockNode = mSM->getRootSceneNode()->createChildSceneNode("clock");

    int lenght = 90;
    float ang = 360 / 12;
    for (int x = 1; x <= 12; x++) {     //Bolas horas de reloj
        Ogre::Entity* sphere = mSM->createEntity("sphere.mesh"); 
        sphereVector.push_back(clockNode->createChildSceneNode("hora" + std::to_string(x)));
        sphereVector.back()->attachObject(sphere);
        
        sphereVector.back()->setPosition(lenght * Ogre::Math::Cos(Ogre::Degree(90 - x * ang)),
                                        lenght * Ogre::Math::Sin(Ogre::Degree(90 - x * ang)), 0);

        sphereVector.back()->setScale(0.1f, 0.1f, 0.1f);
    }      

    /*for (int x = 1; x <= 12; x++) {
            Ogre::SceneNode* node = mSM->getSceneNode("hora" + std::to_string(x));
        if (x % 2 == 0) {
            node->setScale(0.05f, 0.05f, 0.05f);
        }
        else
            node->setScale(0.1f, 0.1f, 0.1f);
    }*/

    //Manecillas
    Ogre::Entity* entity = mSM->createEntity("cube.mesh");
    clockNode->createChildSceneNode("segundero")->attachObject(entity);

    entity = mSM->createEntity("cube.mesh");
    clockNode->createChildSceneNode("minutero")->attachObject(entity);

    entity = mSM->createEntity("cube.mesh");
    clockNode->createChildSceneNode("hora")->attachObject(entity);

    //Transformaciones
    mSM->getSceneNode("hora")->setScale(0.05f, 0.5f, 0.05f);
    mSM->getSceneNode("hora")->roll(Ogre::Degree(-90));
    mSM->getSceneNode("hora")->setPosition((lenght / 4) * Ogre::Math::Cos(Ogre::Degree(0)), (lenght / 4) * Ogre::Math::Sin(Ogre::Degree(0)), 0);

    mSM->getSceneNode("minutero")->setScale(0.03f, 0.7f, 0.03f);
    mSM->getSceneNode("minutero")->setPosition((lenght / 4) * Ogre::Math::Cos(Ogre::Degree(90)), (lenght / 4) * Ogre::Math::Sin(Ogre::Degree(90)), 0);

    mSM->getSceneNode("segundero")->setScale(0.01f, 0.8f, 0.01f);
    mSM->getSceneNode("segundero")->roll(Ogre::Degree(-180));
    mSM->getSceneNode("segundero")->setPosition((lenght / 4) * Ogre::Math::Cos(Ogre::Degree(-90)), (lenght / 4) * Ogre::Math::Sin(Ogre::Degree(-90)), 0);
}
//------------------------------------------------------------------------
void IG2App::scene2()
{
}
//------------------------------------------------------------------------