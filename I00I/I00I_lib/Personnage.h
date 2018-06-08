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
	float health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;
	//entier permettant de savoir le moment o� a �t� lanc� le dernier sort
	unsigned int lastInvocationDate;
	//chargement des sprites associ�es
	void loadSprites();
	// R�cup�re les �v�nements du joystick pour bouger le personnage
	void move(float x, float y);
	// R�cup�re les �venements du joystick pour incanter (ou pas) un sort
	Spell* invoque(float x, float y, bool A, bool B);
public:
	// Constructeur du personnage, appell� au lancement de la partie (emplacement d�termin� par init)
	Personnage(CharacterType type, int init);
	// M�thode appell� lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort);
	// Getter de health -- Utile ?
	int getHealth();
	// R�cup�re les infos du Joystick et agit en fonction
	Spell* Action();
	//mise � jour des sprites
	bool updateSprites() override;
	//retourne un type (pour les collisions)
	std::string getType() override;
	//getter de player (num�ro du joueur)
	int getNumber();
};