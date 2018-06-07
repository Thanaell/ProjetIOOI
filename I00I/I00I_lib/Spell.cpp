#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"
#include "Game.h"

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
Spell::Spell(SpellType myType, b2Body *passedBody, double directionX, double directionY, bool isCharacterFacingRight) : speed(20), type(myType) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	//position du sort varie selon le sens du personnage
	if (isCharacterFacingRight) {
		bodyDef.position.Set(passedBody->GetPosition().x + 10, passedBody->GetPosition().y);
	}
	else {
		bodyDef.position.Set(passedBody->GetPosition().x - 10, passedBody->GetPosition().y);
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
	character.receive(type);
}

bool Spell::updateSprites() {
	return updateMovingSprite((sf::Sprite*)sprites[0].get());
}
