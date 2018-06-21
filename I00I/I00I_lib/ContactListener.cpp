#include "stdafx.h"
#include "ContactListener.h"


//m�thode appel�e d�s qu'il y a un contact entre 2 fixtures
void MyContactListener::BeginContact(b2Contact * contact)
{
	//on r�cup�re les deux objets point�s par la user data du body entr� en collision
	GameObject* bodyUserData1 = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	GameObject* bodyUserData2 = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//si les deux objets ne sont pas null
	if (bodyUserData1 && bodyUserData2) {
		bodyUserData1->startContact(bodyUserData2);
		bodyUserData2->startContact(bodyUserData1);
	}
}