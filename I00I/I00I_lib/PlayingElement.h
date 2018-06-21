#pragma once
#include "Element.h"
#include "GameObject.h"
#include "stdafx.h"
#include "constantes.h"

// Représente un élement du jeu en tant que tel (donc sorcier ou sortilège)
class PlayingElement : public GameObject, public Element {
protected:

	// Indicates if the Element should be destroyed by the Game Object
	bool toDestroy;
	//Booléen indiquant le sens du personnage
	bool isFacingRight;
	bool updateMovingSprite(sf::Sprite* sprite);

public:
	PlayingElement();

	virtual PlayingElement* action();

	virtual float getHealth();

	virtual int getNumber();

	// Indicates if the Element should be destroyed by the Game Object
	bool isToDestroy();

	//	Update every sprite of the Element
	virtual bool updateSprites() = 0;
};