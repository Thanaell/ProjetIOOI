#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"

// Constructeur du sort
Spell::Spell(SpellType myType, b2Body *passedBody) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(passedBody->GetPosition().x, passedBody->GetPosition().y);
	body = world.CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.
	type = myType;
}
// Fonction appelée lors qu'un sort touche un personnage
void Spell::affect(Personnage &character) {
	character.receive(type);
}