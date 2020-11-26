#pragma once
#include "EntidadIG.h"
#include "Plano.h"
#include <OgreMovablePlane.h>
#include <OgreCamera.h>

class Rio :	public EntidadIG{
public:
	Rio(SceneNode *mNode);
	~Rio();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

	void setReflejo();
private:
	Plano* _rio;
	bool _isWater;
	MovablePlane* _mpRef;
	Camera* _camRef;
};


