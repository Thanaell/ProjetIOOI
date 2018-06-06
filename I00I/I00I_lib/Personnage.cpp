#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"


// Constructeur selon un arch�type (TODO: autres arch�types)
Personnage::Personnage(CharacterType myType, int init) :
	player(init), type(myType), lastInvocationDate(clock()) {
	switch (init) {
	case 0:
		isFacingRight = true;
		break;
	case 1:
		isFacingRight = false;
		break;
	}
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
	shape.SetAsBox(WORLD_WIDTH/32,WORLD_HEIGHT/18);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);
	//attributs variables selon le type pass� en argument
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
	double stickX = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::X)) > STICK_SENSIBILITY ?
		sf::Joystick::getAxisPosition(player, sf::Joystick::X) : 0;
	double stickY = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::Y)) > STICK_SENSIBILITY ?
		-sf::Joystick::getAxisPosition(player, sf::Joystick::Y) : 0;
	bool buttonA = sf::Joystick::isButtonPressed(player, 0);
	bool buttonB = sf::Joystick::isButtonPressed(player, 1);
	if (!buttonA && !buttonB) { move(stickX, stickY); return nullptr; }
	return invoque(stickX, stickY, buttonA, buttonB);
}

bool Personnage::updateSprites() {
	return updateMovingSprite();
}


void Personnage::loadSprites() {
	auto& sin = Loader::Instance();
	sf::Sprite* movingSprite = nullptr;
	switch (type)
	{
	case TYPE1:
		movingSprite = new sf::Sprite(*sin.getTexture("wizard1"));
		break;
	default:
		movingSprite = new sf::Sprite(*sin.getTexture("wizard1"));
		break;
	}

	movingSprite->setOrigin(sf::Vector2f(200.f, 200.f));
	movingSprite->setScale(SPRITE_SCALE);
	if(!isFacingRight) movingSprite->scale(sf::Vector2f(-1.f, 1.f));

	sprites.push_back(std::unique_ptr<sf::Sprite>(movingSprite));
}

void Personnage::move(double x, double y) {
	if (x >= 0) {
		isFacingRight = true;
	}
	else {
		isFacingRight = false;
	}
	body->SetLinearVelocity(b2Vec2(PLAYER_VELOCITY * x, PLAYER_VELOCITY * y));
}

Spell * Personnage::invoque(double x, double y, bool A, bool B) {
	unsigned int now = clock();

	if (now - lastInvocationDate > INVOCATION_RECOVERYTIME) {
		lastInvocationDate = clock();
		if (A && !B) return new Spell(spellbook[0], body, x, y, isFacingRight);
		if (!A && B) return new Spell(spellbook[1], body, x, y, isFacingRight);
		if (A && B) return new Spell(spellbook[2], body, x, y, isFacingRight);
	}
	return nullptr;
}
