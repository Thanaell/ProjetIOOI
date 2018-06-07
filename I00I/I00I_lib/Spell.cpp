#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"
#include "Game.h"


void Spell::startContact(Personnage * persoToHit) {
	std::cout << "appel de startContact" << std::endl;
	affect(*persoToHit);
	isContacting = true;
}

bool Spell::getIsContacting()
{
	return isContacting;
}

int Spell::getCaster()
{
	return playerWhoCast;
}

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
		movingSprite = new sf::Sprite(*sin.getTexture("spell1"));
		break;
	}
	movingSprite->setOrigin(sf::Vector2f(100.f, 100.f));
	movingSprite->setScale(SPRITE_SCALE);


	sprites.push_back(std::unique_ptr<sf::Sprite>(movingSprite));
}

// Constructeur du sort
Spell::Spell(SpellType myType, b2Body *passedBody, float directionX, float directionY, bool isCharacterFacingRight, int caster) :
	speed(20), type(myType), isContacting(false), playerWhoCast(caster) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	//position du sort varie selon le sens du personnage
	//si on ne bouge pas le joystick
	if (directionX == 0 && directionY == 0) {
		if (isCharacterFacingRight) {
			bodyDef.position.Set(passedBody->GetPosition().x + 5, passedBody->GetPosition().y);
		}
		else {
			bodyDef.position.Set(passedBody->GetPosition().x - 5, passedBody->GetPosition().y);
		}
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
	circle.m_radius = WORLD_HEIGHT/64;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;

	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);

	//comportements variables selon le type (notamment la vitesse)
	switch (type) {
	case(SORT1):
		speed = 5;
		break;
	}
	//cas où le joystick n'est presque pas incliné
	if (abs(directionX) < 5 && abs(directionY) < 5) {
		if (isCharacterFacingRight) body->SetLinearVelocity(b2Vec2(speed*100,0));
		else body->SetLinearVelocity(b2Vec2(-speed * 100, 0));
	}
	else {
		float racine = sqrt(directionX * directionX + directionY * directionY);
		float xprime = 100 * directionX / racine;
		float yprime = 100 * directionY / racine;
		body->SetLinearVelocity(b2Vec2(xprime * speed, yprime * speed));
	}
	loadSprites();
}
// Fonction appelée lors qu'un sort touche un personnage
void Spell::affect(Personnage &character) {
	std::cout << "passage dans affect"<<std::endl;
	character.receive(type);
}

bool Spell::updateSprites() {
	return updateMovingSprite((sf::Sprite*)sprites[0].get());
}

std::string Spell::getType()
{
	return "spell";
}
