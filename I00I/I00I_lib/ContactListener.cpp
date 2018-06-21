#include "stdafx.h"
#include "ContactListener.h"


//méthode appelée dès qu'il y a un contact entre 2 fixtures
void MyContactListener::BeginContact(b2Contact * contact)
{
	//on récupère les deux objets pointés par la user data du body entré en collision
	GameObject* bodyUserData1 = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	GameObject* bodyUserData2 = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//si les deux objets ne sont pas null
	if (bodyUserData1 && bodyUserData2) {
		bodyUserData1->startContact(bodyUserData2);
		bodyUserData2->startContact(bodyUserData1);
	}
}