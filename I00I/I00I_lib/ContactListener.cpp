#include "stdafx.h"
#include "ContactListener.h"

//méthode appelée dès qu'il y a un contact entre 2 fixtures
void MyContactListener::BeginContact(b2Contact * contact)
{
	//on récupère les deux objets pointés par la user data du body entré en collision
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

	//si les deux objets ne sont pas null
	if (bodyUserData1 && bodyUserData2) {
		//cas des collisions entre un personnage et un spell 
		if (static_cast<PlayingElement*>(bodyUserData1)->getType() == "personnage" && static_cast<PlayingElement*>(bodyUserData2)->getType() == "spell") {
			//on ignore les collisions entre un sort et le personnage qui l'a lancé
			if (static_cast<Spell*>(bodyUserData2)->getCaster() != static_cast<Personnage*>(bodyUserData1)->getNumber()) {
				//on appelle la méthode startContact du sort sur le personnage
				static_cast<Spell*>(bodyUserData2)->startContact(static_cast<Personnage*>(bodyUserData1));
			}
		}
		if (static_cast<PlayingElement*>(bodyUserData1)->getType() == "spell" && static_cast<PlayingElement*>(bodyUserData2)->getType() == "personnage") {
			//on ignore les collisions entre un sort et le personnage qui l'a lancé
			if (static_cast<Spell*>(bodyUserData1)->getCaster() != static_cast<Personnage*>(bodyUserData2)->getNumber()) {
				//on appelle la méthode startContact du sort sur le personnage
				static_cast<Spell*>(bodyUserData1)->startContact(static_cast<Personnage*>(bodyUserData2));
			}
		}
	}
}