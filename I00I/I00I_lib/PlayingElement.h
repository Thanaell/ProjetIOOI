#pragma once
#include "Element.h"
#include "stdafx.h"

// Représente un élement du jeu en tant que tel (donc sorcier ou sortilège)
class PlayingElement : public Element {
protected:
	// pointeur vers le corps de l'élément de jeu telle que défini dans le monde b2World
	b2Body* body;
	///	C'est un pointeur classique car b2World est propriétaire de ses élément et détruit lui meme l'instance des body
	/// donc a la destruction de cette classe, il n'y a pas besoin de détuire l'élément pointé par ce pointeur
public:
	//getter du body (au moins pour les tests)
	b2Body* getBody();

	virtual void updateSprites() = 0;
	
};