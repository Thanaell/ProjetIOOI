#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"

//void Personnage::move(sf::Event event) {
//	b2Vec2 velocity;
//	//mouvement sur l'axe x (facteur à ajuster)
//	if (event.joystickMove.axis == 0) {
//		velocity.x = event.joystickMove.position;
//		velocity.y = body->GetLinearVelocity().y;
//	}
//	//mouvement sur l'axe y (facteur à ajuster)
//	if (event.joystickMove.axis == 1) {
//		velocity.x = body->GetLinearVelocity().x;
//		velocity.y = event.joystickMove.position;
//	}
//	body->SetLinearVelocity(velocity);
//}


// Constructeur selon un archétype (TODO: autres archétypes)
Personnage::Personnage(CharacterType myType, int init) :
	player(init), type(myType), lastInvocationDate(std::chrono::system_clock::now()) {
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
	if(!buttonA && !buttonB)
	return invoque(stickX, stickY, buttonA, buttonB);
}

//Spell * Personnage::Action(sf::Event event) {
//	switch (event.type)
//	{
//	case sf::Event::EventType::JoystickMoved:
//		move(event);
//		break;
//	case sf::Event::EventType::JoystickButtonPressed:
//		return invoque(event);
//		break;
//	default:
//		break;
//	}
//	return nullptr;
//}

//pour le moment, renvoie toujours un spell de type 1
//Spell * Personnage::invoque(sf::Event event) {
//	Spell * mySpell;
//	switch (event.joystickButton.button) {
//	case(1):
//		mySpell = new Spell(SORT1, body);
//		break;
//	default:
//		mySpell = new Spell(SORT1, body);
//	}
//	return mySpell;
//}

void Personnage::move(double x, double y) {
	body->SetLinearVelocity(b2Vec2(x, y));
}

Spell * Personnage::invoque(double x, double y, bool A, bool B) {
	auto now = std::chrono::system_clock::now();
	int durationSinceInvoque = std::chrono::duration_cast<std::chrono::microseconds>(now - lastInvocationDate).count();

	if (durationSinceInvoque > INVOCATION_RECOVERYTIME) {
		lastInvocationDate = std::chrono::system_clock::now();
		if (A && !B) return new Spell(SORT1, body);
	}
	return nullptr;
}
