#pragma once
#include "stdafx.h"
#include "PlayingElement.h"

class Personnage;

// Représente un sortilège
class Spell : public PlayingElement {

protected:
	//entier indiquant qui a lancé le sort
	int playerWhoCast;
	// Nom du sort
	std::string name;
	// Type du sort
	SpellType type;
	// Portée du sort
	float range;
	// Contient l'angle du joystick au moment de l'invocation du sort
	float theta;
	// Power of the spell
	float power;

	virtual void movingStrategy();

	void loadSprites();


public:
	static Spell* createSpell(SpellType myType, b2Body *body, float directionX, float directionY, bool isCharacterFacingRight, int caster);
	// Constructeur du sort
	Spell(SpellType myType, b2Body *body, float directionX, float directionY, bool isCharacterFacingRight, int caster);
	// retourne false si le sprite n'est plus dans la zone de jeu
	bool updateSprites() override;
	//gestion de la collision avec un personnage
	void startContact(GameObject *objectToHit) override;
	//getter de playerWhoCast (entier du perso qui a lancé le sort)
	int getCaster() const;

	float getPower() const;

	PlayingElement* action() override;

	SpellType getType() const;
};
