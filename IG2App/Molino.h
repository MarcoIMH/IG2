#pragma 
#include "AspasMolino.h"


class Molino: public OgreBites::InputListener
{
public:
	Molino(SceneManager* mSM);
	~Molino();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
private:
	SceneNode* mNode;
	SceneNode* cilindroNode;
	SceneNode* esferaNode;
	SceneNode* aspasNode;
	AspasMolino* aspas;
};

