#pragma once
#include "EntidadIG.h"
#include "Plano.h"
#include <OgreMovablePlane.h>
#include <OgreCamera.h>
#include <OgreRenderTargetListener.h>

class Rio :	public EntidadIG, public RenderTargetListener{
public:
	Rio(SceneNode *mNode);
	~Rio();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) override;
	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) override;

	void setReflejo();
private:
	Plano* _rio;
	bool _isWater;
	MovablePlane* _mpRef;
	Camera* _camRef;
};


