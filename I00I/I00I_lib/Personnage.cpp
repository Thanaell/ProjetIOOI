#include "stdafx.h"
#include "Personnage.h"
#include "Spell.h"

void Personnage::mouve(sf::Event event) {}

Spell * Personnage::invoque(sf::Event) {
	return nullptr;
}

//Constructeur selon un archétype (TODO: autres archétypes)
Personnage::Personnage(CharacterType type) {
	switch (type) {
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
		mouve(event);
		break;
	case sf::Event::EventType::KeyPressed:
		return invoque(event);
		break;
	default:
		break;
	}
	return nullptr;
}
