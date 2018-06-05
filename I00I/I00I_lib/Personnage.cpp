#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"
#include "Game.h"

void Personnage::move(sf::Event event) {}



//Constructeur selon un archétype (TODO: autres archétypes)
Personnage::Personnage(CharacterType myType) {
	type = myType;
	//initialisation du body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);//on démarre en (0,0), valeurs à ajuster
	body = Game::getWorld().CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(50.0f, 10.0f);
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
		break;
	}
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

Spell * Personnage::Action(sf::Event event) {
	switch (event.type)
	{
	case sf::Event::EventType::JoystickMoved:
		move(event);
		break;
	case sf::Event::EventType::KeyPressed:
		return invoque(event);
		break;
	default:
		break;
	}
	return nullptr;
}

//pour le moment, renvoie toujours un spell de type 1
Spell * Personnage::invoque(sf::Event event) {
	Spell * mySpell = new Spell(SORT1, body);
	return mySpell;
}