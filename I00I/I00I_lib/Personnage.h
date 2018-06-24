#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "Gauge.h"

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

	Gauge health;


	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;
	//entier permettant de savoir le moment o� a �t� lanc� le dernier sort
	unsigned int lastInvocationDate;

	// entier permettant de savoir le moment o� a �t� recu le dernier sort
	unsigned int lastDammage;
	// entier permettant de savoir le moment o� a �t� recu le dernier sort
	unsigned int lastDammageFeedback;

	//chargement des sprites associ�es
	void loadSprites();
	// R�cup�re les �v�nements du joystick pour bouger le personnage
	void move(float x, float y);

	
	Gauge shieldGauge;
	// Indicate is the player is protected against attack
	bool isProtected;

	Gauge absorbingGauge;
	// Indicate is the player is protected against attack
	bool isAbsorbing;
	int frameAbsorbingLeft;

	// R�cup�re les �venements du joystick pour incanter (ou pas) un sort
	PlayingElement* invoque(float x, float y, bool A, bool B);

	// Methode managing player shield
	void shieldManagement(bool isCasting);

	std::string spriteName;


	// Constructeur du personnage, appell� au lancement de la partie (emplacement d�termin� par init)
	Personnage(CharacterType type, int init, std::string spriteName);

public:
	// M�thode appell� lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	//	Retourne false si le sort n'a pas affect� le personnage
	receiveResult receive(SpellType sort, sf::Vector2f spellPosition, int caster) override;
	// Getter de health 
	float getHealth() override;
	// R�cup�re les infos du Joystick et agit en fonction
	PlayingElement* action() override;
	//mise � jour des sprites
	bool updateSprites() override;
	//getter de player (num�ro du joueur)
	int getNumber() override;
};