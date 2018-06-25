#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"
#include "Perso1.h"
#include "Perso2.h"

Personnage::Personnage(CharacterType myType, int init, std::string spriteName) :
	PlayingElement(),
	player(init),
	type(myType),
	lastInvocationDate(clock()),
	lastDammage(0),
	lastDammageFeedback(DAMMAGE_SPRITE_DURATION),
	spriteName(spriteName),
	isProtected(false),
	isAbsorbing(false),
	frameAbsorbingLeft(ABSORPTION_DURATION),
	health(DAMMAGE_RECOVERY, new Gauge(HEALTH_COLOR, HEALTH_POSITION(init), HELTH_SIZE, init == 0 ? TOPLEFT : TOPRIGHT)),
	shieldGauge(SHIELD_GAUGE_COLOR, SHIELD_GAUGE_POSITION(init), SHIELD_GAUGE_SIZE, init == 0 ? TOPLEFT : TOPRIGHT, PROTECTION_DURATION, PROTECTION_DURATION, false),
	absorbingGauge(ABSORBING_GAUGE_COLOR, ABSORBING_GAUGE_POSITION(init), ABSORBING_GAUGE_SIZE, init == 0 ? TOPLEFT : TOPRIGHT, ABSORPTION_NEEDED)
{
	isFacingRight = init == 0;

	//initialisation du body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(PLAYER_POSITION_X(init), PLAYER_POSITION_Y);
	body = Game::getWorld()->CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape shape;
	shape.SetAsBox(PLAYER_SIZE_B2D_X, PLAYER_SIZE_B2D_Y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = PLAYER_DENSITY;
	fixtureDef.friction = PLAYER_FRICTION;
	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);


	auto& sin = Loader::Instance();
	sounds.push_back(std::unique_ptr<sf::Sound>(new sf::Sound(*sin.getSound("death"))));

	loadSprites();
}

receiveResult Personnage::receive(SpellType sort, sf::Vector2f spellPosition, int caster) {
	receiveResult result;

	auto spritePosition = ((sf::Sprite*)sprites[0].get())->getPosition();

	if (isProtected) {
		result.affectTarget = false;
		result.destroyBullet = false;
		result.returnBullet = true;
	} else if (isAbsorbing) {
		result.affectTarget = false;
		result.destroyBullet = true;
		result.returnBullet = true;
		switch (sort) {
		case SORT1: absorbingGauge += POWER_SORT_1; break;
		case SORT2: absorbingGauge += POWER_SORT_2; break;
		case SORT3: absorbingGauge.refill(); break;
		default:
			absorbingGauge.add(10);
			break;
		}

		lastDammageFeedback.start();

		lastDammageFeedback.getObject()->setPosition(spritePosition);
		lastDammageFeedback.getObject()->setColor(sf::Color::White);
		if (spritePosition.x - spellPosition.x < 0 && lastDammageFeedback.getObject()->getScale().x < 0
			|| spritePosition.x - spellPosition.x > 0 && lastDammageFeedback.getObject()->getScale().x > 0) {
			lastDammageFeedback.getObject()->scale(sf::Vector2f(-1.f, 1.f));
		}
	} else if (caster == player && !CAN_AFFECT_OWNER) {
		result.affectTarget = false;
		result.destroyBullet = false;
		result.returnBullet = false;
	} else if(health.isDone()) {
		result.affectTarget = true;
		result.destroyBullet = true;
		result.returnBullet = false;


		switch (sort) {
		case SORT1: health.getObject()->remove(POWER_SORT_1); break;
		case SORT2: health.getObject()->remove(POWER_SORT_2); break;
		case SORT3: health.getObject()->remove(POWER_SORT_3); break;
		default:
			health.getObject()->remove(10);
			break;
		}


		lastDammageFeedback.start();
		health.start();

		lastDammageFeedback.getObject()->setPosition(spritePosition);
		lastDammageFeedback.getObject()->setColor(sf::Color::White);
		if (spritePosition.x - spellPosition.x < 0 && lastDammageFeedback.getObject()->getScale().x < 0
			|| spritePosition.x - spellPosition.x > 0 && lastDammageFeedback.getObject()->getScale().x > 0) {
			lastDammageFeedback.getObject()->scale(sf::Vector2f(-1.f, 1.f));
		}

		if (health.getObject()->isEmpty()) sounds[0]->play();
	} else {
		result.affectTarget = false;
		result.destroyBullet = false;
		result.returnBullet = false;
	}
	return result;
}

float Personnage::getHealth() {
	return health.getObject()->getValue();
}

PlayingElement * Personnage::action() {
	PlayingElement* result = nullptr;

	for (auto& s : spellbook) s.update();
	lastDammageFeedback.update();
	health.update();

	if (lastDammageFeedback.isDone()) lastDammageFeedback.getObject()->setColor(sf::Color::Transparent);
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

	// gestion du bouclier si on ne lance pas un sort durant cette frame
	shieldManagement(buttonA || buttonB);

	if (!buttonA && !buttonB) { move(stickX, stickY); return result; }
	result = invoque(stickX, stickY, buttonA, buttonB);
	return result;
}

bool Personnage::updateSprites() {
	if (isProtected) updateMovingSprite((sf::Sprite*)sprites[2].get());
	if (isAbsorbing) updateMovingSprite((sf::Sprite*)sprites[3].get());
	return updateMovingSprite((sf::Sprite*)sprites[0].get());
}

int Personnage::getNumber() {
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
	sprites.push_back(std::shared_ptr<sf::Sprite>(dammage));
	lastDammageFeedback.setObject(dammage);

	//	Sprite marquant que le personnage est affecté par un sort
	sf::Sprite* shield = new sf::Sprite(*sin.getTexture("shieldPlayer"));
	shield->setOrigin(PLAYER_SPRITE_ORIGINE);
	shield->setScale(SPRITE_SCALE);
	shield->setColor(sf::Color::Transparent);
	if (!isFacingRight) shield->scale(sf::Vector2f(-1.f, 1.f));
	sprites.push_back(std::unique_ptr<sf::Sprite>(shield));

	//	Sprite marquant que le personnage est affecté par un sort
	sf::Sprite* absorbingShield = new sf::Sprite(*sin.getTexture("absorbingShield"));
	absorbingShield->setOrigin(PLAYER_SPRITE_ORIGINE);
	absorbingShield->setScale(SPRITE_SCALE);
	absorbingShield->setColor(sf::Color::Transparent);
	if (!isFacingRight) absorbingShield->scale(sf::Vector2f(-1.f, 1.f));
	sprites.push_back(std::unique_ptr<sf::Sprite>(absorbingShield));

	for (auto& s : health.getObject()->getSprites()) sprites.push_back(std::shared_ptr<sf::Drawable>(s));
	for (auto& s : shieldGauge.getSprites()) sprites.push_back(std::shared_ptr<sf::Drawable>(s));
	for (auto& s : absorbingGauge.getSprites()) sprites.push_back(std::shared_ptr<sf::Drawable>(s));
}


// Fonction a réécrire pour la rendre plus belle
void Personnage::move(float x, float y) {
	isFacingRight = x == 0 ? isFacingRight : x > 0;
	auto speed = body->GetLinearVelocity();

	float wantedVelocityX = vitesse * (x > 0 ? 1 : -1);
	float wantedVelocityY = vitesse * (y > 0 ? 1 : -1);

	float speedRatioX = speed.x / wantedVelocityX;
	float speedRatioY = speed.y / wantedVelocityY;
	body->ApplyLinearImpulseToCenter(b2Vec2(PLAYER_INERTIE * x * (1.f - speedRatioX), PLAYER_INERTIE * y * (1.f - speedRatioY)), true);
}


PlayingElement * Personnage::invoque(float x, float y, bool A, bool B) {
	unsigned int now = clock();
	PlayingElement* result = nullptr;

	if (now - lastInvocationDate > INVOCATION_RECOVERYTIME) {
		lastInvocationDate = clock();
		if (A && !B && spellbook[0].isDone()) {
			result = Spell::createSpell(*spellbook[0].getObject(), body, x, y, isFacingRight, player);
			spellbook[0].start();
		}
		if (!A && B && spellbook[1].isDone()) {
			result = Spell::createSpell(*spellbook[1].getObject(), body, x, y, isFacingRight, player);
			spellbook[1].start();
		}
		if (A && B && absorbingGauge.isFull()) {
			result = Spell::createSpell(*spellbook[2].getObject(), body, x, y, isFacingRight, player);
			absorbingGauge.setValue(0.f);
		}
	}
	
	return result;
}

void Personnage::shieldManagement(bool isCasting) {
	sf::Sprite* shield = (sf::Sprite*)sprites[2].get();
	sf::Sprite* absorbingShield = (sf::Sprite*)sprites[3].get();


	if (sf::Joystick::isButtonPressed(player, 4) 
	|| (((!sf::Joystick::isConnected(0) && player == 0)
	|| (!sf::Joystick::isConnected(1) && player == 1 && sf::Joystick::isConnected(0)))
	&& sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))) {
		isAbsorbing = false;
		absorbingShield->setColor(sf::Color::Transparent);

		if (!shieldGauge.isEmpty() && !isCasting) {
			isProtected = true;
			shieldGauge -= 2.f;
			shield->setColor(sf::Color(255, 255, 255, 255 * shieldGauge.getRatio()));
		} else {
			isProtected = false;
			shield->setColor(sf::Color::Transparent);
		}
	} else {
		isProtected = false;
		shieldGauge += 1.f;
		shield->setColor(sf::Color::Transparent);


		if (sf::Joystick::isButtonPressed(player, 5)
			|| (((!sf::Joystick::isConnected(0) && player == 0)
				|| (!sf::Joystick::isConnected(1) && player == 1 && sf::Joystick::isConnected(0)))
				&& sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
			if (frameAbsorbingLeft > 0 && !isCasting) {
				isAbsorbing = true;
				frameAbsorbingLeft = std::max(frameAbsorbingLeft - 2, 0);
				absorbingShield->setColor(sf::Color(255, 255, 255, 128));
			}
			else {
				isAbsorbing = false;
				absorbingShield->setColor(sf::Color::Transparent);
			}
		}
		else {
			isAbsorbing = false;
			frameAbsorbingLeft = std::min(frameAbsorbingLeft + 1, ABSORPTION_DURATION);
			absorbingShield->setColor(sf::Color::Transparent);
		}
	}
}
