#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"

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
	case SORT1:
	default:
		health -= 10;
		break;
	}
	((sf::RectangleShape*)sprites[2].get())->setScale(sf::Vector2f(health / 100.f > 0.f ? health / 100.f : 0, 1.f));
}

int Personnage::getHealth() {
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
	if (!sf::Joystick::isConnected(0) && player == 0) {
		stickX = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? -50.f :
				 sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? 50.f : 0.f;
		stickY = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? 50.f :
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? -50.f : 0.f;
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

	//	Sprite marquant que le personnage est affecté par un sort
	sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite()));

	sf::RectangleShape* barreVie = new sf::RectangleShape(HELTH_SIZE);
	barreVie->setOrigin(sf::Vector2f(player == 0 ? 0.f: HELTH_W_SIZE, 0.f));
	barreVie->setPosition(sf::Vector2f(player == 0 ? 50.f : W_WIDTH - 50.f, 50.f));
	barreVie->setFillColor(sf::Color::Color(0xe040109a));
	sprites.push_back(std::unique_ptr<sf::RectangleShape>(barreVie));
}

void Personnage::move(float x, float y) {
	if (x > 0) {
		isFacingRight = true;
	}
	else if (x <0){
		isFacingRight = false;
	}
	body->SetLinearVelocity(b2Vec2(PLAYER_VELOCITY * x, PLAYER_VELOCITY * y));
}

Spell * Personnage::invoque(float x, float y, bool A, bool B) {
	unsigned int now = clock();

	if (now - lastInvocationDate > INVOCATION_RECOVERYTIME) {
		lastInvocationDate = clock();
		if (A && !B) return new Spell(spellbook[0], body, x, y, isFacingRight,player);
		if (!A && B) return new Spell(spellbook[1], body, x, y, isFacingRight,player);
		if (A && B) return new Spell(spellbook[2], body, x, y, isFacingRight,player);
	}
	return nullptr;
}
