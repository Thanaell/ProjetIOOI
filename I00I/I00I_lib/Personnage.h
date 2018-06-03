#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"
#include "CharacterType.h"

typedef class Spell;

// Représente un sorcier dans le jeu
class Personnage : public PlayingElement {
	// Nom du personnage
	std::string name;
	// Point de vie
	int health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;
public:
	// Constructeur du personnage, appellé au lancement de la partie
	Personnage(CharacterType type);
	// Méthode appellé lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort);
	//getter de health
	int getHealth();
};