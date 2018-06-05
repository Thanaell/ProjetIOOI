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
	circle.m_radius = 0.5f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;

	body->CreateFixture(&fixtureDef);
	type = myType;
	body->SetUserData(this);

	//comportements variables selon le type (notamment la vitesse)
	switch (myType) {
	case(SORT1):
		body->SetLinearVelocity(b2Vec2(0, 2));
		break;
	}
	
}
// Fonction appelée lors qu'un sort touche un personnage
void Spell::affect(Personnage &character) {
	character.receive(type);
}