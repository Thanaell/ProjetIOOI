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
	//Archétype
	CharacterType type;
	// Point de vie
	int health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;

	// Récupère les évènements du joystick pour bouger le personnage
	void move(sf::Event event);

	// Récupère les évenements du joystick pour incanter (ou pas) un sort
	Spell* invoque(sf::Event);
public:
	// Constructeur du personnage, appellé au lancement de la partie
	Personnage(CharacterType type);
	// Méthode appellé lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort);
	// Getter de health -- Utile ?
	int getHealth();

	// Action du personnage en fonction des input de la manette
	Spell* Action(sf::Event event);
};