#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"
#include "CharacterType.h"

typedef class Spell;

// Repr�sente un sorcier dans le jeu
class Personnage : public PlayingElement {
	// Nom du personnage
	std::string name;
	//Arch�type
	CharacterType type;
	// Point de vie
	int health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;

	// R�cup�re les �v�nements du joystick pour bouger le personnage
	void move(sf::Event event);

	// R�cup�re les �venements du joystick pour incanter (ou pas) un sort
	Spell* invoque(sf::Event);
public:
	// Constructeur du personnage, appell� au lancement de la partie
	Personnage(CharacterType type);
	// M�thode appell� lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort);
	// Getter de health -- Utile ?
	int getHealth();

	// Action du personnage en fonction des input de la manette
	Spell* Action(sf::Event event);
};