#pragma once
#include "Element.h"
#include "GameObject.h"
#include "stdafx.h"
#include "constantes.h"

// Repr�sente un �lement du jeu en tant que tel (donc sorcier ou sortil�ge)
class PlayingElement : public GameObject, public Element {
protected:

	// Indicates if the Element should be destroyed by the Game Object
	bool toDestroy;
	//Bool�en indiquant le sens du personnage
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