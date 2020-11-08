#pragma 
#include "AspasMolino.h"

class Molino: public EntidadIG{
public:
	Molino(SceneNode *mNode);
	~Molino();
	virtual bool keyPressed (const OgreBites::KeyboardEvent& evt);  // InputListener
	virtual void frameRendered(const Ogre::FrameEvent& evnt) override;
private:
	SceneNode* nodoFicticioCentro;
	SceneNode* cilindroNode;
	SceneNode* esferaNode;
	SceneNode* aspasNode;
	AspasMolino* aspas;

	Entity* cupula;
	bool r_event = false;
};

