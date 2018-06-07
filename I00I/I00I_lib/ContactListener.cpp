#include "stdafx.h"
#include "ContactListener.h"

void MyContactListener::BeginContact(b2Contact * contact)
{
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyUserData1 && bodyUserData2) {
		std::cout <<"1: " << static_cast<PlayingElement*>(bodyUserData1)->getType();
		std::cout << "2: " << static_cast<PlayingElement*>(bodyUserData2)->getType();
		if (static_cast<PlayingElement*>(bodyUserData1)->getType() == "personnage" && static_cast<PlayingElement*>(bodyUserData2)->getType() == "spell") {
		/*	if (static_cast<Spell*>(bodyUserData2)->getCaster() != static_cast<Personnage*>(bodyUserData1)->getNumber()) {
				static_cast<Spell*>(bodyUserData2)->startContact(static_cast<Personnage*>(bodyUserData1));
			}*/
		}
		if (static_cast<PlayingElement*>(bodyUserData1)->getType() == "spell" && static_cast<PlayingElement*>(bodyUserData2)->getType() == "personnage") {
			/*if (static_cast<Spell*>(bodyUserData1)->getCaster() != static_cast<Personnage*>(bodyUserData2)->getNumber()) {
				static_cast<Spell*>(bodyUserData1)->startContact(static_cast<Personnage*>(bodyUserData2));
			}*/
		}
	}
}