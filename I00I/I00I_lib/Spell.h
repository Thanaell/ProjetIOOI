#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"

typedef class Personnage;

// Repr�sente un sortil�ge
class Spell : public PlayingElement {
	// Nom du sort
	std::string name;
	// Type du sort
	SpellType type;
	// Port�e du sort
	double range;
	// Vitesse du sort
	double speed;
public:
	// Constructeur du sort
	Spell(SpellType myType, b2Body *body);
	// Fonction appel� lors qu'un sort touche un personnage
	void affect(Personnage &character);
};
