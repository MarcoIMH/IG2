#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "EntidadIG.h"
#include "Molino.h"
#include "Avion.h"
#include "Plano.h"


class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
  void setScene(int scene = 0) { sceneId = scene; };

protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;

private:
    int sceneId = 0;
    void scene0();
    void scene1();
    void scene2();
    void scene3();
    void scene4();
    void scene5();
    void scene6();
    void scene7();
    std::vector<EntidadIG*> sceneObjects;
    Plano* water;
};

#endif
