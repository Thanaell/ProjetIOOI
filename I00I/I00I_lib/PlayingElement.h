#pragma once
#include "Element.h"
#include "GameObject.h"
#include "stdafx.h"
#include "constantes.h"

// Représente un élement du jeu en tant que tel (donc sorcier ou sortilège)
class PlayingElement : public GameObject, public Element {
protected:
	
	//Booléen indiquant le sens du personnage
	bool isFacingRight;
	bool updateMovingSprite(sf::Sprite* sprite);

public:
	virtual bool updateSprites() = 0;
};