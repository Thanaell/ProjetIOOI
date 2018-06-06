#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"


// Constructeur selon un archétype (TODO: autres archétypes)
Personnage::Personnage(CharacterType myType, int init) :
	player(init), type(myType), lastInvocationDate(clock()) {
	//initialisation du body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	switch (init) {
	case 0:
		bodyDef.position.Set(0, 10);
		break;
	case 1:
		bodyDef.position.Set(100, 10);
		break;
	}
	body = Game::getWorld()->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(50.0f, 10.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);
	//attributs variables selon le type passé en argument
	switch (myType) {
	case TYPE1:
		health = 100;
		spellbook.push_back(SORT1);
		spellbook.push_back(SORT1);
		spellbook.push_back(SORT1);
		break;
	}
}

void Personnage::receive(SpellType sort) {
	switch (sort) {
	case TYPE1:
		health -= 10;
		break;
	}
}

int Personnage::getHealth() {
	return health;
}

Spell * Personnage::Action() {
	double stickX = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::X)) > 5 ?
		sf::Joystick::getAxisPosition(player, sf::Joystick::X) : 0;
	double stickY = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::Y)) > 5 ?
		sf::Joystick::getAxisPosition(player, sf::Joystick::Y) : 0;
	bool buttonA = sf::Joystick::isButtonPressed(player, 0);
	bool buttonB = sf::Joystick::isButtonPressed(player, 1);
	if (!buttonA && !buttonB) { move(stickX, stickY); return nullptr; }
	return invoque(stickX, stickY, buttonA, buttonB);
}


void Personnage::move(double x, double y) {
	body->SetLinearVelocity(b2Vec2(x, y));
}

Spell * Personnage::invoque(double x, double y, bool A, bool B) {
	unsigned int now = clock();

	if (now - lastInvocationDate > INVOCATION_RECOVERYTIME) {
		lastInvocationDate = clock();
		if (A && !B) return new Spell(spellbook[0], body, x, y);
		if (!A && B) return new Spell(spellbook[1], body, x, y);
		if (A && B) return new Spell(spellbook[2], body, x, y);
	}
	return nullptr;
}
