#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"
#include "CharacterType.h"

class Spell;

// Repr�sente un sorcier dans le jeu
class Personnage : public PlayingElement {
	// Nom du personnage
	std::string name;
	//Arch�type
	CharacterType type;
	// Num�ro du joueur
	int player;
	// Point de vie
	int health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;

	// R�cup�re les �v�nements du joystick pour bouger le personnage
	//void move(sf::Event event);
	void move(double x, double y);

	// R�cup�re les �venements du joystick pour incanter (ou pas) un sort
	//Spell* invoque(sf::Event);
	Spell* invoque(double x, double y, bool A, bool B);
public:
	// Constructeur du personnage, appell� au lancement de la partie (emplacement d�termin� par init)
	Personnage(CharacterType type, int init);
	// M�thode appell� lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort);
	// Getter de health -- Utile ?
	int getHealth();

	// R�cup�re les infos du Joystick et agit en fonction
	Spell* Action();

	// Action du personnage en fonction des input de la manette
	//Spell* Action(sf::Event event);
};