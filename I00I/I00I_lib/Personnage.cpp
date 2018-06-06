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
		bodyDef.position.Set(WORLD_WIDTH/8,WORLD_HEIGHT/5);
		break;
	case 1:
		bodyDef.position.Set(7*WORLD_WIDTH/8,WORLD_HEIGHT/5);
		break;
	}
	body = Game::getWorld()->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(WORLD_WIDTH/8,WORLD_HEIGHT/5);
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
		spellbook.push_back(SORT2);
		spellbook.push_back(SORT3);
		break;
	case TYPE2:
		health = 100;
		spellbook.push_back(SORT4);
		spellbook.push_back(SORT5);
		spellbook.push_back(SORT6);
		break;
	}

	loadSprites();
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
		-sf::Joystick::getAxisPosition(player, sf::Joystick::Y) : 0;
	bool buttonA = sf::Joystick::isButtonPressed(player, 0);
	bool buttonB = sf::Joystick::isButtonPressed(player, 1);
	if (!buttonA && !buttonB) { move(stickX, stickY); return nullptr; }
	return invoque(stickX, stickY, buttonA, buttonB);
}

void Personnage::updateSprites() {
	auto b2position = body->GetPosition();
	sf::Vector2f position(b2position.x - 72, W_HEIGHT - b2position.y - 144);
	((sf::Sprite *)sprites[0].get())->setPosition(position);
#ifdef DEBUG_LOG
	std::cout << "Position du joueur " << player << " (" << position.x << ", " << position.y << ")" << std::endl;
#endif
}


void Personnage::loadSprites() {
	auto& sin = Loader::Instance();
	sf::Vector2f scale(.2f, .2f);
	auto b2position = body->GetPosition();
	sf::Vector2f position(b2position.x - 72, W_HEIGHT - b2position.y - 144);
	switch (type)
	{
	case TYPE1:
		sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*sin.getTexture("wizard1"))));
		break;
	default:
		sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*sin.getTexture("wizard1"))));
		break;
	}
	((sf::Sprite *)sprites[0].get())->setScale(scale);
	((sf::Sprite *)sprites[0].get())->setPosition(position);
}

void Personnage::move(double x, double y) {
	body->SetLinearVelocity(b2Vec2(3*x, 3*y));
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
