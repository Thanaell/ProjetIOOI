#pragma once
#include "Element.h"
#include "GameObject.h"
#include "stdafx.h"
#include "constantes.h"

// Repr�sente un �lement du jeu en tant que tel (donc sorcier ou sortil�ge)
class PlayingElement : public GameObject, public Element {
protected:
	
	//Bool�en indiquant le sens du personnage
	bool isFacingRight;
	bool updateMovingSprite(sf::Sprite* sprite);

public:
	virtual bool updateSprites() = 0;
};