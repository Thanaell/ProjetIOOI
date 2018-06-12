#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"
#include "CharacterType.h"

class Spell;

// Repr�sente un sorcier dans le jeu
class Personnage : public PlayingElement {
public:
	static Personnage* createPersonnage(CharacterType myType, int init);

protected:
	// Nom du personnage
	std::string name;
	//Vitesse
	float vitesse;
	//Arch�type
	CharacterType type;
	// Num�ro du joueur
	int player;
	//Vie maximale
	float maxHealth;
	// Point de vie
	float health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;
	//entier permettant de savoir le moment o� a �t� lanc� le dernier sort
	unsigned int lastInvocationDate;
	// entier permettant de savoir le moment o� a �t� recu le dernier sort
	unsigned int lastDammage;
	//chargement des sprites associ�es
	void loadSprites();
	// R�cup�re les �v�nements du joystick pour bouger le personnage
	void move(float x, float y);
	// R�cup�re les �venements du joystick pour incanter (ou pas) un sort
	Spell* invoque(float x, float y, bool A, bool B);

	std::string spriteName;


	// Constructeur du personnage, appell� au lancement de la partie (emplacement d�termin� par init)
	Personnage(CharacterType type, int init, std::string spriteName);

public:
	// M�thode appell� lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort, sf::Vector2f spellPosition);
	// Getter de health 
	float getHealth();
	// R�cup�re les infos du Joystick et agit en fonction
	Spell* Action();
	//mise � jour des sprites
	bool updateSprites() override;
	//retourne un type (pour les collisions)
	std::string getType() override;
	//getter de player (num�ro du joueur)
	int getNumber();
};