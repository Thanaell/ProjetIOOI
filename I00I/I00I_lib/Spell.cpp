#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"
#include "Game.h"
#include "Spell1.h"
#include "Spell2.h"
#include "Spell3.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// m�thode appel�e en cas de contact avec un personnage
void Spell::startContact(GameObject *objectToHit) {
	std::cout << "appel de startContact" << std::endl;
	receiveResult result = objectToHit->receive(this, ((sf::Sprite*)sprites[0].get())->getPosition(), playerWhoCast);
	toDestroy = result.destroyBullet;

	if (result.returnBullet) {
		playerWhoCast = -1;
		auto velocity = body->GetLinearVelocity();
		body->SetLinearVelocity(b2Vec2(velocity.x * -1, velocity.y * -1));
	}
}


// getter de playerWhoCast
int Spell::getCaster() const {
	return playerWhoCast;
}

float Spell::getPower() const {
	return power;
}

PlayingElement * Spell::action() {
	++lifeTime;
	movingStrategy();
	return nullptr;
}

SpellType Spell::getType() const {
	return type;
}

void Spell::movingStrategy() {}

void Spell::loadSprites() {
	auto& sin = Loader::Instance();
	sf::Sprite* movingSprite = nullptr;
	switch (type)
	{
	case SORT1:
		movingSprite = new sf::Sprite(*sin.getTexture("spell1"));
		break;
	case SORT2:
		movingSprite = new sf::Sprite(*sin.getTexture("spell2"));
		break;
	case SORT3:
		movingSprite = new sf::Sprite(*sin.getTexture("spell3"));
		break;
	default:
		movingSprite = new sf::Sprite(*sin.getTexture("spell2"));
		break;
	}
	movingSprite->setOrigin(SPELL_SPRITE_ORIGINE);
	movingSprite->setScale(SPRITE_SCALE);


	sprites.push_back(std::unique_ptr<sf::Sprite>(movingSprite));
}

Spell * Spell::createSpell(SpellType myType, b2Body * body, float directionX, float directionY, bool isCharacterFacingRight, int caster) {
	Spell* retour = nullptr;
	switch (myType)
	{
	case SORT1: 
		retour = new Spell1(body, directionX, directionY, isCharacterFacingRight, caster);
		break;
	case SORT2:
		retour = new Spell2(body, directionX, directionY, isCharacterFacingRight, caster);
		break;
	case SORT3:
		retour = new Spell3(body, directionX, directionY, isCharacterFacingRight, caster);
		break;
	default: retour = new Spell1(body,directionX,directionY,isCharacterFacingRight,caster);
		break;
	}
	return retour;
}


// Constructeur du sort
Spell::Spell(SpellType myType, b2Body *passedBody, float directionX, float directionY, bool isCharacterFacingRight, int caster) :
	PlayingElement(),
	type(myType),
	playerWhoCast(caster) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	//position du sort varie selon le sens du personnage
	//si on ne bouge pas le joystick
	if (directionX == 0 && directionY == 0) {
		bodyDef.position.Set(passedBody->GetPosition().x + (isCharacterFacingRight ? 5 : -5), passedBody->GetPosition().y);
	}
	//si on indique une direction
	else {
		float racine = sqrt(directionX * directionX + directionY * directionY);
		float xprime = 100 * directionX / racine;
		float yprime = 100 * directionY / racine;
		bodyDef.position.Set(passedBody->GetPosition().x + xprime/20, passedBody->GetPosition().y + yprime/20);
	}

	body = Game::getWorld()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = SPELL_SIZE_B2D;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	
	lifeTime = 0;
	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);

// D�placement par d�faut du sort
	//cas o� le joystick n'est presque pas inclin�
	if (abs(directionX) < 5 && abs(directionY) < 5) {
		body->SetLinearVelocity(b2Vec2((isCharacterFacingRight ? SPEED_SORT_1 : -SPEED_SORT_1) * COEF_SPELL_SPEED, 0));
		theta = isCharacterFacingRight ? 0 : M_PI;
	}
	else {
		float racine = sqrt(directionX * directionX + directionY * directionY);
		float xprime = COEF_SPELL_SPEED * directionX / racine;
		float yprime = COEF_SPELL_SPEED * directionY / racine;
		body->SetLinearVelocity(b2Vec2(xprime * SPEED_SORT_1, yprime * SPEED_SORT_1));
		
		theta = std::acos(directionX / racine) * (directionY < 0 ? -1 : 1);
	}
	body->SetAngularVelocity(100.f);
	loadSprites();
}

bool Spell::updateSprites() {
	return updateMovingSprite((sf::Sprite*)sprites[0].get());
}