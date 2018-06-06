#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"

class Personnage;

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


	void loadSprites();
public:
	// Constructeur du sort
	Spell(SpellType myType, b2Body *body, double directionX, double directionY);
	// Fonction appel� lors qu'un sort touche un personnage
	void affect(Personnage &character);


	void updateSprites() override;
};
