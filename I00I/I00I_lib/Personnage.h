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


	unsigned int lastInvocationDate;

	void loadSprites();

	// Récupère les évènements du joystick pour bouger le personnage
	void move(float x, float y);

	// Récupère les évenements du joystick pour incanter (ou pas) un sort
	Spell* invoque(float x, float y, bool A, bool B);
public:
	// Constructeur du personnage, appellé au lancement de la partie (emplacement déterminé par init)
	Personnage(CharacterType type, int init);
	// Méthode appellé lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort);
	// Getter de health -- Utile ?
	int getHealth();

	// Récupère les infos du Joystick et agit en fonction
	Spell* Action();

	bool updateSprites() override;

	//retourne un type (pour les collisions)
	std::string getType() override;
	int getNumber();
};