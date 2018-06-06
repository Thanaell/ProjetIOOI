#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"
#include "CharacterType.h"

class Spell;

// Représente un sorcier dans le jeu
class Personnage : public PlayingElement {
	// Nom du personnage
	std::string name;
	//Archétype
	CharacterType type;
	// Numéro du joueur
	int player;
	// Point de vie
	int health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;

	std::chrono::time_point<std::chrono::system_clock> lastInvocationDate;

	// Récupère les évènements du joystick pour bouger le personnage
	void move(double x, double y);

	// Récupère les évenements du joystick pour incanter (ou pas) un sort
	Spell* invoque(double x, double y, bool A, bool B);
public:
	// Constructeur du personnage, appellé au lancement de la partie (emplacement déterminé par init)
	Personnage(CharacterType type, int init);
	// Méthode appellé lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort);
	// Getter de health -- Utile ?
	int getHealth();

	// Récupère les infos du Joystick et agit en fonction
	Spell* Action();

};