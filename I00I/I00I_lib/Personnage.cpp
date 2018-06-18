#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"
#include "Perso1.h"
#include "Perso2.h"

Personnage::Personnage(CharacterType myType, int init, std::string spriteName) :
	player(init),
	type(myType),
	lastInvocationDate(clock()),
	lastDammage(0),
	spriteName(spriteName),
	isProtected(false)
{
	isFacingRight = init == 0;

	//initialisation du body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(PLAYER_POSITION_X(init), PLAYER_POSITION_Y);
	body = Game::getWorld()->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(PLAYER_SIZE_B2D_X, PLAYER_SIZE_B2D_Y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = PLAYER_DENSITY;
	fixtureDef.friction = PLAYER_FRICTION;
	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);

	loadSprites();
}

bool Personnage::receive(SpellType sort, sf::Vector2f spellPosition) {
	if (isProtected) return false;
	switch (sort) {
	case SORT1: health -= POWER_SORT_1; break;
	case SORT2: health -= POWER_SORT_2; break;
	case SORT3: health -= POWER_SORT_3; break;
	default:
		health -= 10;
		break;
	}
	((sf::RectangleShape*)sprites[3].get())->setScale(sf::Vector2f(health / maxHealth > 0.f ? health / maxHealth : 0, 1.f));
	lastDammage = clock();
	auto spritePosition = ((sf::Sprite*)sprites[0].get())->getPosition();
	((sf::Sprite*)sprites[1].get())->setPosition(spritePosition);
	((sf::Sprite*)sprites[1].get())->setColor(sf::Color::White);
	if (spritePosition.x - spellPosition.x < 0 && ((sf::Sprite*)sprites[1].get())->getScale().x < 0
		|| spritePosition.x - spellPosition.x > 0 && ((sf::Sprite*)sprites[1].get())->getScale().x > 0) {
		((sf::Sprite*)sprites[1].get())->scale(sf::Vector2f(-1.f, 1.f));
	}
	return true;
}

float Personnage::getHealth() {
	return health;
}

Spell * Personnage::Action() {
	if (clock() - lastDammage > DAMMAGE_SPRITE_DURATION) ((sf::Sprite*)sprites[1].get())->setColor(sf::Color::Transparent);
	float stickX = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::X)) > STICK_SENSIBILITY ?
		sf::Joystick::getAxisPosition(player, sf::Joystick::X) : 0;
	float stickY = abs(sf::Joystick::getAxisPosition(player, sf::Joystick::Y)) > STICK_SENSIBILITY ?
		-sf::Joystick::getAxisPosition(player, sf::Joystick::Y) : 0;
	bool buttonA = sf::Joystick::isButtonPressed(player, 0);
	bool buttonB = sf::Joystick::isButtonPressed(player, 1);

	// gestion du bouclier
	if (sf::Joystick::isButtonPressed(player, 4)) {
		if (protectionDuration > 0) {
			isProtected = true;
			protectionDuration = std::max(protectionDuration - 1, 0);
			//((sf::Sprite*)sprites[2].get())->setColor(sf::Color::Color(0xFFFFFF00 + 255 * (protectionDuration / PROTECTION_DURATION * 3 / 4 + 1 / 4)));
			((sf::Sprite*)sprites[2].get())->setColor(sf::Color::White);
		}
		else {
			isProtected = false;
			((sf::Sprite*)sprites[2].get())->setColor(sf::Color::Transparent);
		}
	} else {
		isProtected = false;
		protectionDuration = std::min(protectionDuration + 1, PROTECTION_DURATION);
		((sf::Sprite*)sprites[2].get())->setColor(sf::Color::Transparent);
	}

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
	if (isProtected) updateMovingSprite((sf::Sprite*)sprites[2].get());
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
	sf::Sprite* movingSprite = new sf::Sprite(*sin.getTexture(spriteName));

	movingSprite->setOrigin(PLAYER_SPRITE_ORIGINE);
	movingSprite->setScale(SPRITE_SCALE);
	if(!isFacingRight) movingSprite->scale(sf::Vector2f(-1.f, 1.f));
	sprites.push_back(std::unique_ptr<sf::Sprite>(movingSprite));

	//	Sprite marquant que le personnage est affecté par un sort
	sf::Sprite* dammage = new sf::Sprite(*sin.getTexture("dammagePlayer"));
	dammage->setOrigin(PLAYER_SPRITE_ORIGINE);
	dammage->setScale(SPRITE_SCALE);
	dammage->setColor(sf::Color::Transparent);
	if (!isFacingRight) dammage->scale(sf::Vector2f(-1.f, 1.f));
	sprites.push_back(std::unique_ptr<sf::Sprite>(dammage));

	//	Sprite marquant que le personnage est affecté par un sort
	sf::Sprite* shield = new sf::Sprite(*sin.getTexture("shieldPlayer"));
	shield->setOrigin(PLAYER_SPRITE_ORIGINE);
	shield->setScale(SPRITE_SCALE);
	shield->setColor(sf::Color::Transparent);
	if (!isFacingRight) shield->scale(sf::Vector2f(-1.f, 1.f));
	sprites.push_back(std::unique_ptr<sf::Sprite>(shield));

	sf::RectangleShape* barreVie = new sf::RectangleShape(HELTH_SIZE);
	barreVie->setOrigin(HEALTH_ORIGINE(player));
	barreVie->setPosition(HEALTH_POSITION(player));
	barreVie->setFillColor(HEALTH_COLOR);
	sprites.push_back(std::unique_ptr<sf::RectangleShape>(barreVie));

	sf::Sprite* interfacePlayer = new sf::Sprite(*sin.getTexture("interfacePlayer"));
	interfacePlayer->setOrigin(INTERFACE_PLAYER_ORIGINE(player));
	interfacePlayer->setScale(INTERFACE_PLAYER_SCALE);
	interfacePlayer->setPosition(INTERFACE_PLAYER_POSITION(player));
	sprites.push_back(std::unique_ptr<sf::Sprite>(interfacePlayer));
}

void Personnage::move(float x, float y) {
	isFacingRight = x == 0 ? isFacingRight : x > 0;
	body->ApplyLinearImpulseToCenter(b2Vec2(PLAYER_INERTIE * x, PLAYER_INERTIE * y), true);
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
