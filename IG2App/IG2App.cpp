#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_h) {
      if (sceneId == 1) {     
          SceneNode* centro = mSM->getSceneNode("manecillas");    
          SceneNode* segundero = mSM->getSceneNode("segundero");   

          Ogre::Real distanciaAlCentro = centro->convertLocalToWorldPosition(Vector3(0, 0, 0)).distance(segundero->convertLocalToWorldPosition(Vector3(0, 0, 0)));
          segundero->setPosition(0, 0, 0);
          segundero->roll(Ogre::Degree(3), Ogre::Node::TS_WORLD);
          segundero->translate(Vector3(0, distanciaAlCentro, 0), Ogre::Node::TS_LOCAL);
          segundero->translate(centro->convertLocalToWorldPosition(Vector3(0, 0, 0)), Ogre::Node::TS_WORLD);
      }
  }
  else if (evt.keysym.sym == SDLK_g) {
      if (sceneId == 1) {
          if (mSM->getSceneNode("clock") != nullptr) {
              mSM->getSceneNode("manecillas")->roll(Ogre::Degree(3));    //Rota reloj
          }
      }   
  }
  else if (evt.keysym.sym == SDLK_j) {
      if (sceneId == 3) {
          if (mSM->getSceneNode("tierra") != nullptr) {
              SceneNode* tierra = mSM->getSceneNode("tierra");
              SceneNode* sol = mSM->getSceneNode("sol");
              SceneNode* luna = mSM->getSceneNode("luna");
                 
              Ogre::Real distanceSolTierra = sol->convertLocalToWorldPosition(Vector3(0, 0, 0)).distance(tierra->convertLocalToWorldPosition(Vector3(0, 0, 0)));
              Ogre::Real distanceTierraLuna = tierra->convertLocalToWorldPosition(Vector3(0, 0, 0)).distance(luna->convertLocalToWorldPosition(Vector3(0, 0, 0)));;
              tierra->setPosition(0, 0, 0);
              tierra->yaw(Ogre::Degree(-3), Ogre::Node::TS_WORLD);
              tierra->translate(Vector3(distanceSolTierra, 0, 0), Ogre::Node::TS_LOCAL);
              tierra->translate(sol->convertLocalToWorldPosition(Vector3(0, 0, 0)), Ogre::Node::TS_WORLD);

              luna->setPosition(0, 0, 0);
              luna->yaw(Ogre::Degree(3), Ogre::Node::TS_WORLD);
              luna->translate(Vector3(distanceTierraLuna, 0, 0), Ogre::Node::TS_LOCAL);
              luna->translate(tierra->convertLocalToWorldPosition(Vector3(0, 0, 0)), Ogre::Node::TS_WORLD);
          }
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
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));    //Scene background color

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -0.75, -1));  //vec3.normalise();
  //mLightNode->setDirection(Ogre::Vector3(0, 1, 0));  //vec3.normalise();
  //mLightNode->setDirection(Ogre::Vector3(0, -1, 0));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  setScene(1);
  switch (sceneId) {
  case 0: scene0(); break;
  case 1: scene1(); break;
  case 2: scene2(); break;  // Molino
  case 3: scene3(); break;  // Sistema solar
  case 4: scene4(); break;  // Avión
  case 5: scene5(); break;  // Plano Antes de Entidad IG
  case 6: scene6(); break;  // Plano y molino después de Entidad IG
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
    Ogre::SceneNode* manecillasNode = mSM->getRootSceneNode()->createChildSceneNode("manecillas");
    manecillasNode->setPosition(0, 0, 0);
    Ogre::Entity* entity = mSM->createEntity("cube.mesh");
    manecillasNode->createChildSceneNode("segundero")->attachObject(entity);

    entity = mSM->createEntity("cube.mesh");
    manecillasNode->createChildSceneNode("minutero")->attachObject(entity);

    entity = mSM->createEntity("cube.mesh");
    manecillasNode->createChildSceneNode("hora")->attachObject(entity);

    //Transformaciones
    mSM->getSceneNode("hora")->setScale(0.05f, 0.5f, 0.05f);
    SceneNode* manecilla = mSM->getSceneNode("hora");
    manecilla->setPosition(0, 0, 0);
    manecilla->roll(Degree(-90), Node::TS_WORLD);
    manecilla->translate(Vector3(0, lenght / 8, 0), Node::TS_LOCAL);
    manecilla->translate(manecillasNode->convertLocalToWorldPosition(Vector3(0, 0, 0)), Node::TS_WORLD);

    //mSM->getSceneNode("hora")->translate(0, lenght / 4, 0);
    //mSM->getSceneNode("hora")->roll(Ogre::Degree(-90), Ogre::Node::TS_PARENT);
    //mSM->getSceneNode("hora")->setPosition((lenght / 4) * Ogre::Math::Cos(Ogre::Degree(0)), (lenght / 4) * Ogre::Math::Sin(Ogre::Degree(0)), 0);

    manecilla = mSM->getSceneNode("minutero");
    manecilla->setScale(0.03f, 0.7f, 0.03f);
    manecilla->translate(Vector3(0, lenght / 5, 0), Node::TS_LOCAL);

    //mSM->getSceneNode("minutero")->setScale(0.03f, 0.7f, 0.03f);
    //mSM->getSceneNode("minutero")->translate(0, lenght / 4, 0);
    //mSM->getSceneNode("minutero")->setPosition((lenght / 4) * Ogre::Math::Cos(Ogre::Degree(90)), (lenght / 4) * Ogre::Math::Sin(Ogre::Degree(90)), 0);

    manecilla = mSM->getSceneNode("segundero");
    manecilla->setScale(0.01f, 0.8f, 0.01f);
    manecilla->setPosition(0, 0, 0);
    manecilla->roll(Degree(-230), Node::TS_WORLD);
    manecilla->translate(Vector3(0, lenght / 5, 0), Node::TS_LOCAL);
    manecilla->translate(manecillasNode->convertLocalToWorldPosition(Vector3(0, 0, 0)), Node::TS_WORLD);

    //mSM->getSceneNode("segundero")->setScale(0.01f, 0.8f, 0.01f);
    //mSM->getSceneNode("segundero")->translate(0, lenght / 4, 0);
    //mSM->getSceneNode("segundero")->roll(Ogre::Degree(-230), Ogre::Node::TS_PARENT);
    //mSM->getSceneNode("segundero")->setPosition((lenght / 4) * Ogre::Math::Cos(Ogre::Degree(-140)), (lenght / 4) * Ogre::Math::Sin(Ogre::Degree(-140)), 0);
}
//------------------------------------------------------------------------
void IG2App::scene2()
{
    //SceneNode* aspaNode = mSM->getRootSceneNode()->createChildSceneNode("aspa");
    //SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero");
    //SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno");

    //Ogre::Entity* ent = mSM->createEntity("cube.mesh");
    //tableroNode->attachObject(ent);
    //tableroNode->setScale(1.8f, 0.3f, 0.02f);
    ////tableroNode->translate(10, 10, 10);

    //ent = mSM->createEntity("Barrel.mesh");
    //cilindroNode->attachObject(ent);
    //cilindroNode->translate(80, 0, 5);
    //cilindroNode->setScale(1.5f, 4.0f, 1.5f);

    /*int num = 12;
    float ang = 360 / num;
    SceneNode* aspasNode = mSM->getRootSceneNode()->createChildSceneNode("aspas");
    for (int x = 0; x < num; x++) {
        SceneNode* aspaNode = aspasNode->createChildSceneNode("aspa_"+std::to_string(x+1));
        SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(x+1));
        SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(x+1));

        Ogre::Entity* ent = mSM->createEntity("cube.mesh");
        tableroNode->attachObject(ent);
        tableroNode->setScale(1.6f, 0.4f, 0.02f);
        
        ent = mSM->createEntity("Barrel.mesh");
        cilindroNode->attachObject(ent);
        cilindroNode->translate(60, 0, 5);
        cilindroNode->setScale(1.5f, 4.0f, 1.5f);
        

        aspaNode->setPosition( 80* Ogre::Math::Cos(Ogre::Degree(x * ang)),
            80 * Ogre::Math::Sin(Ogre::Degree(x * ang)), 0);

        aspaNode->roll(Ogre::Degree(x*ang));
        cilindroNode->roll(Ogre::Degree(-x * ang));
    }*/

    SceneNode* molinoNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
    Molino* m = new Molino(molinoNode);   
    sceneObjects.push_back(m);
    //EntidadIG::addListener(molino);
    //addInputListener(molino);
}
void IG2App::scene3()
{
    Real position = 400;
    Real radioTierra = 400;
    Real radioLuna = 100;

    SceneNode* sol = mSM->getRootSceneNode()->createChildSceneNode("sol");
    Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
    sol->attachObject(ent);
    sol->scale(0.5f, 0.5f, 0.5f);
    sol->setPosition(position, 0, 0);

    SceneNode* tierra = mSM->getRootSceneNode()->createChildSceneNode("tierra");
    ent = mSM->createEntity("sphere.mesh");
    tierra->attachObject(ent);
    tierra->scale(0.3f, 0.3f, 0.3f);
    tierra->setPosition(position, 0, 0);
    tierra->yaw(Ogre::Degree(180), Ogre::Node::TS_LOCAL);
    tierra->translate(Vector3(radioTierra, 0, 0), Ogre::Node::TS_LOCAL);

    SceneNode* luna = mSM->getRootSceneNode()->createChildSceneNode("luna");
    ent = mSM->createEntity("sphere.mesh");
    luna->attachObject(ent);
    luna->scale(0.1f, 0.1f, 0.1f);
    luna->setPosition(tierra->convertLocalToWorldPosition(Vector3(0, 0, 0)));
    luna->yaw(Ogre::Degree(180), Ogre::Node::TS_LOCAL);
    luna->translate(Vector3(radioLuna, 0, 0), Ogre::Node::TS_LOCAL);
}

void IG2App::scene4() {
    SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode("avion");
    Avion* a = new Avion(avionNode);
    sceneObjects.push_back(a);
}

void IG2App::scene5()
{
    MeshManager::getSingleton().createPlane("mPlane1080x800",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z);
    Entity* ent = mSM->createEntity("mPlane1080x800");
    SceneNode* planeNode = mSM->getRootSceneNode();
    planeNode->attachObject(ent);
}

void IG2App::scene6()
{
    //AGUA
    SceneNode* planoAguaNode = mSM->getRootSceneNode()->createChildSceneNode();
    Plano* p = new Plano(planoAguaNode, "PlanoAgua");
    sceneObjects.push_back(p);

    //MOLINO Y SU PLANO
    SceneNode* molinoNode = mSM->getRootSceneNode()->createChildSceneNode();
    Molino* m = new Molino(molinoNode);     
    sceneObjects.push_back(m);
    //Transformaciones molino
    molinoNode->translate(450, 190, -240);

    SceneNode* planoMolinoNode = mSM->getRootSceneNode()->createChildSceneNode();
    Plano* pM = new Plano(planoMolinoNode, "PlanoMolino");    
    sceneObjects.push_back(pM);
    //Transformaciones plano molino
    planoMolinoNode->scale(0.2f, 1.0f, 0.3f);
    planoMolinoNode->translate(430, 0, -280);

    //SINBAD Y SU PLANO
    SceneNode* sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
    Entity* sinbad = mSM->createEntity("Sinbad.mesh");    
    sinbadNode->attachObject(sinbad);
    //Transformaciones sinbad
    sinbadNode->setScale(8, 8, 8);
    sinbadNode->translate(-300, 40, 200);

    SceneNode* planoSinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
    Plano* pS = new Plano(planoSinbadNode, "PlanoSinbad");    
    sceneObjects.push_back(pS);
    //Transformaciones plano sinbad
    planoSinbadNode->translate(-300, 0, 200);
    planoSinbadNode->setScale(0.3f, 1.0f, 0.4f);

    //AVION
    SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode();
    Avion* avion = new Avion(avionNode);
    sceneObjects.push_back(avion);  
    //Transformaciones AVion
    avionNode->setScale(0.1f, 0.1f, 0.1f);
    avionNode->translate(0, 400, 0);
}
   
//------------------------------------------------------------------------