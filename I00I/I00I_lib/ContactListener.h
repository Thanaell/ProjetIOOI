#include "stdafx.h"
#include "GameObject.h"

//classe gérant les collision. Une instance du contactlistener est utilisée par le world
class MyContactListener : public b2ContactListener {

public:
	//méthode appelée dès qu'il y a un contact entre 2 fixtures
	void BeginContact(b2Contact* contact);

};