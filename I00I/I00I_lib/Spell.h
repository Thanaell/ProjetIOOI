#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"

class Personnage;

// Représente un sortilège
class Spell : public PlayingElement {
	//entier indiquant qui a lancé le sort
	int playerWhoCast;
	//Booléen indiquant si le sort a touché un personnage
	bool isContacting;
	// Nom du sort
	std::string name;
	// Type du sort
	SpellType type;
	// Portée du sort
	double range;
	// Vitesse du sort
	double speed;


	void loadSprites();
public:
	// Constructeur du sort
	Spell(SpellType myType, b2Body *body, double directionX, double directionY, bool isCharacterFacingRight, int caster);
	// Fonction appelé lors qu'un sort touche un personnage
	void affect(Personnage &character);

	// retourne false si le sprite n'est plus dans la zone de jeu
	bool updateSprites() override;
	//retourne un type (pour les collisions)
	std::string getType() override;
	//gestion de la collision avec un personnage
	void startContact(Personnage *persoToHit);
	bool getIsContacting();
	int getCaster();
};
