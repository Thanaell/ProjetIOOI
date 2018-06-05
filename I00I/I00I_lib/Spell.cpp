#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"
#include "Game.h"

// Constructeur du sort
Spell::Spell(SpellType myType, b2Body *passedBody) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(passedBody->GetPosition().x, passedBody->GetPosition().y);
	body = Game::getWorld()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_p.Set(2.0f, 3.0f);
	circle.m_radius = 0.5f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
	type = myType;
	body->SetUserData(this);
	
}
// Fonction appelée lors qu'un sort touche un personnage
void Spell::affect(Personnage &character) {
	character.receive(type);
}