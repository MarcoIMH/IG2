#pragma 
#include "AspasMolino.h"

class Molino: public EntidadIG{
public:
	Molino(SceneNode *mNode);
	~Molino();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
private:
	SceneNode* nodoFicticioCentro;
	SceneNode* cilindroNode;
	SceneNode* esferaNode;
	SceneNode* aspasNode;
	AspasMolino* aspas;
};

