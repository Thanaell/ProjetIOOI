#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);

	
};