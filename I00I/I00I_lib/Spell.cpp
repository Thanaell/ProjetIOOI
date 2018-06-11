#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"
#include "Game.h"
#include "Spell1.h"
#include "Spell2.h"
#include "Spell3.h"



//m�thode appel�e en cas de contact avec un personnage
void Spell::startContact(Personnage * persoToHit) {
	std::cout << "appel de startContact" << std::endl;
	affect(*persoToHit);
	isContacting = true;
}

//getter de isContacting
bool Spell::getIsContacting()
{
	return isContacting;
}

//getter de playerWhoCast
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
		movingSprite = new sf::Sprite(*sin.getTexture("spell2"));
		break;
	}
	movingSprite->setOrigin(sf::Vector2f(100.f, 100.f));
	movingSprite->setScale(SPRITE_SCALE);


	sprites.push_back(std::unique_ptr<sf::Sprite>(movingSprite));
}

Spell * Spell::createSpell(SpellType myType, b2Body * body, float directionX, float directionY, bool isCharacterFacingRight, int caster)
{
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
	default: retour = new Spell(SORT1,body,directionX,directionY,isCharacterFacingRight,caster);
		break;
	}
	return retour;
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

	
	//cas o� le joystick n'est presque pas inclin�
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
// Fonction appel�e lors qu'un sort touche un personnage
void Spell::affect(Personnage &character) {
	character.receive(type);
}

bool Spell::updateSprites() {
	return updateMovingSprite((sf::Sprite*)sprites[0].get());
}

//indique qu'un spell est de type "spell" (pour la gestion des collisions)
std::string Spell::getType()
{
	return "spell";
}
