#include "stdafx.h"
#include "GameObject.h"

//classe g�rant les collision. Une instance du contactlistener est utilis�e par le world
class MyContactListener : public b2ContactListener {

public:
	//m�thode appel�e d�s qu'il y a un contact entre 2 fixtures
	void BeginContact(b2Contact* contact);

};