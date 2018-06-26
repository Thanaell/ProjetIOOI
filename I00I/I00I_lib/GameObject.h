#pragma once

#include "stdafx.h"
#include "constantes.h"

class Spell;

class GameObject {
protected:
	// pointeur vers le corps de l'élément de jeu telle que défini dans le monde b2World
	b2Body* body;
	///	C'est un pointeur classique car b2World est propriétaire de ses élément et détruit lui meme l'instance des body
	/// donc a la destruction de cette classe, il n'y a pas besoin de détuire l'élément pointé par ce pointeur

	int lifeTime;
public:
	//getter du body (au moins pour les tests)
	b2Body* getBody();
	//indique le type de l'élément (pour la gestion des collisions)
	void startContact();


	virtual receiveResult receive(Spell * sort, sf::Vector2f spellPosition, int caster);

	virtual void startContact(GameObject *objectToHit);

	~GameObject();
};