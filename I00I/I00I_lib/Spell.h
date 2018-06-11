#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"

class Personnage;

// Repr�sente un sortil�ge
class Spell : public PlayingElement {

protected:
	//entier indiquant qui a lanc� le sort
	int playerWhoCast;
	//Bool�en indiquant si le sort a touch� un personnage
	bool isContacting;
	// Nom du sort
	std::string name;
	// Type du sort
	SpellType type;
	// Port�e du sort
	float range;
	// Vitesse du sort
	float speed;


	void loadSprites();
public:
	static Spell* createSpell(SpellType myType, b2Body *body, float directionX, float directionY, bool isCharacterFacingRight, int caster);
	// Constructeur du sort
	Spell(SpellType myType, b2Body *body, float directionX, float directionY, bool isCharacterFacingRight, int caster, float vitesse);
	// Fonction appel� lors qu'un sort touche un personnage
	void affect(Personnage &character);
	// retourne false si le sprite n'est plus dans la zone de jeu
	bool updateSprites() override;
	//retourne un type (pour les collisions)
	std::string getType() override;
	//gestion de la collision avec un personnage
	void startContact(Personnage *persoToHit);
	//getter de IsContacting (true si le sort a touch� un personnage autre que son anceur)
	bool getIsContacting();
	//getter de playerWhoCast (entier du perso qui a lanc� le sort)
	int getCaster();
};
