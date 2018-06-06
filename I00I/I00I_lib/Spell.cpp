#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"
#include "Game.h"

void Spell::loadSprites() {
	auto& sin = Loader::Instance();
	sf::Vector2f scale(.2f, .2f);
	auto b2position = body->GetPosition();
	sf::Vector2f position(b2position.x - 36, W_HEIGHT - b2position.y - 72);
	switch (type)
	{
	case SORT1:
		sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*sin.getTexture("spell1"))));
		break;
	case SORT2:
		sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*sin.getTexture("spell2"))));
		break;
	case SORT3:
		sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*sin.getTexture("spell3"))));
		break;
	default:
		sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*sin.getTexture("spell1"))));
		break;
	}
	((sf::Sprite *)sprites[0].get())->setScale(scale);
	((sf::Sprite *)sprites[0].get())->setPosition(position);
}

// Constructeur du sort
Spell::Spell(SpellType myType, b2Body *passedBody, double directionX, double directionY) {
	b2BodyDef bodyDef;
	int speedFactor;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(passedBody->GetPosition().x, passedBody->GetPosition().y);
	body = Game::getWorld()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 0.5f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;

	body->CreateFixture(&fixtureDef);
	type = myType;
	body->SetUserData(this);

	//comportements variables selon le type (notamment la vitesse)
	switch (myType) {
	case(SORT1):
		speedFactor = 1;
		break;
	default:
		speedFactor = 2;
	}
	body->SetLinearVelocity(b2Vec2(directionX*speedFactor, directionY*speedFactor));
	loadSprites();
}
// Fonction appelée lors qu'un sort touche un personnage
void Spell::affect(Personnage &character) {
	character.receive(type);
}

void Spell::updateSprites() {
	auto b2position = body->GetPosition();
	sf::Vector2f position(b2position.x - 36, W_HEIGHT - b2position.y - 36);
	((sf::Sprite *)sprites[0].get())->setPosition(position);
}
