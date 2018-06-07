#pragma once
#include "Element.h"
#include "stdafx.h"
#include "constantes.h"
#include <string>

// Repr�sente un �lement du jeu en tant que tel (donc sorcier ou sortil�ge)
class PlayingElement : public Element {
protected:
	// pointeur vers le corps de l'�l�ment de jeu telle que d�fini dans le monde b2World
	b2Body* body;
	///	C'est un pointeur classique car b2World est propri�taire de ses �l�ment et d�truit lui meme l'instance des body
	/// donc a la destruction de cette classe, il n'y a pas besoin de d�tuire l'�l�ment point� par ce pointeur

	//Bool�en indiquant le sens du personnage
	bool isFacingRight;

	bool updateMovingSprite(sf::Sprite* sprite);

public:

	~PlayingElement();
	//getter du body (au moins pour les tests)
	b2Body* getBody();
	virtual std::string getType()=0;
	virtual bool updateSprites() = 0;
	
};