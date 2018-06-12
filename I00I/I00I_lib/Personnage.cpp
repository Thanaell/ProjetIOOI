#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"
#include "Perso1.h"
#include "Perso2.h"

Personnage::Personnage(CharacterType myType, int init, std::string spriteName) :
	player(init), type(myType), lastInvocationDate(clock()), spriteName(spriteName) {
	isFacingRight = init == 0;

	//initialisation du body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(PLAYER_POSITION_X(init), PLAYER_POSITION_Y);
	body = Game::getWorld()->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(WORLD_WIDTH/32,WORLD_HEIGHT/18);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = PLAYER_DENSITY;
	fixtureDef.friction = PLAYER_FRICTION;
	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);

	loadSprites();
}

void Personnage::receive(SpellType sort) {
	switch (sort) {
	case SORT1:
	default:
		health -= 10;
		break;
	}
	((sf::RectangleShape*)sprites[2].get())->setScale(sf::Vector2f(health / maxHealth > 0.f ? health / maxHealth : 0, 1.f));
}

float Personnage::getHealth() {
	return health;
}

Spell * Personnage::Action() {
	float stickX = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::X)) > STICK_SENSIBILITY ?
		sf::Joystick::getAxisPosition(player, sf::Joystick::X) : 0;
	float stickY = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::Y)) > STICK_SENSIBILITY ?
		-sf::Joystick::getAxisPosition(player, sf::Joystick::Y) : 0;
	bool buttonA = sf::Joystick::isButtonPressed(player, 0);
	bool buttonB = sf::Joystick::isButtonPressed(player, 1);

	//	S'il n'y a pas de manette connectée
	if ((player == 0 && !sf::Joystick::isConnected(0))
	 || (player == 1 && !sf::Joystick::isConnected(1) && sf::Joystick::isConnected(0))) {
		stickX = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? -KEYBOARD_ACTION :
				 sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? KEYBOARD_ACTION : 0.f;
		stickY = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? KEYBOARD_ACTION :
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? -KEYBOARD_ACTION : 0.f;
		buttonA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		buttonB = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	}

	if (!buttonA && !buttonB) { move(stickX, stickY); return nullptr; }
	return invoque(stickX, stickY, buttonA, buttonB);
}

bool Personnage::updateSprites() {
	return updateMovingSprite((sf::Sprite*)sprites[0].get());
}

std::string Personnage::getType()
{
	return "personnage";
}

int Personnage::getNumber()
{
	return player;
}


Personnage* Personnage::createPersonnage(CharacterType myType, int init) {
	Personnage* retour = nullptr;
	switch (myType)
	{
	case TYPE1: retour = new Perso1(init); break;
	case TYPE2:
		retour = new Perso2(init);
		break;
	default: retour = new Perso1(init); break;
	}
	return retour;
}

void Personnage::loadSprites() {
	auto& sin = Loader::Instance();
	sf::Sprite* movingSprite = nullptr;
	movingSprite = new sf::Sprite(*sin.getTexture(spriteName));

	movingSprite->setOrigin(PLAYER_SPRITE_ORIGINE);
	movingSprite->setScale(SPRITE_SCALE);
	if(!isFacingRight) movingSprite->scale(sf::Vector2f(-1.f, 1.f));
	sprites.push_back(std::unique_ptr<sf::Sprite>(movingSprite));

	//	Sprite marquant que le personnage est affecté par un sort
	sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite()));

	sf::RectangleShape* barreVie = new sf::RectangleShape(HELTH_SIZE);
	barreVie->setOrigin(sf::Vector2f(player == 0 ? 0.f: HELTH_W_SIZE, 0.f));
	barreVie->setPosition(sf::Vector2f(player == 0 ? 50.f : W_WIDTH - 50.f, 50.f));
	barreVie->setFillColor(sf::Color::Color(0xe040109a));
	sprites.push_back(std::unique_ptr<sf::RectangleShape>(barreVie));
}

void Personnage::move(float x, float y) {
	isFacingRight = x == 0 ? isFacingRight : x > 0;
	body->SetLinearVelocity(b2Vec2(PLAYER_VELOCITY * x, PLAYER_VELOCITY * y));
}

Spell * Personnage::invoque(float x, float y, bool A, bool B) {
	unsigned int now = clock();

	if (now - lastInvocationDate > INVOCATION_RECOVERYTIME) {
		lastInvocationDate = clock();
		if (A && !B) return Spell::createSpell(spellbook[0], body, x, y, isFacingRight, player);
		if (!A && B) return Spell::createSpell(spellbook[1], body, x, y, isFacingRight, player);
		if (A && B) return Spell::createSpell(spellbook[2], body, x, y, isFacingRight, player);
	}
	return nullptr;
}
