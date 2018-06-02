#pragma once
#include "stdafx.h"
#include "Personnage.h"
#include "PlayingElement.h"
#include "SpellType.h"


// Représente un sortilège
class Spell : public PlayingElement {
	// Nom du sort
	std::string name;
	// Type du sort
	SpellType type;
	// Portée du sort
	double range;
	// Vitesse du sort
	double speed;
public:
	// Constructeur du sort
	Spell(SpellType myType);
	// Fonction appelé lors qu'un sort touche un personnage
	void affect(Personnage &character);
};
