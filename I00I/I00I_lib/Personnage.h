#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"
#include "CharacterType.h"

class Spell;

// Représente un sorcier dans le jeu
class Personnage : public PlayingElement {
public:
	static Personnage* createPersonnage(CharacterType myType, int init);

protected:
	// Nom du personnage
	std::string name;
	//Vitesse
	float vitesse;
	//Archétype
	CharacterType type;
	// Numéro du joueur
	int player;
	//Vie maximale
	float maxHealth;
	// Point de vie
	float health;
	// Liste des sort que ce personnage peut lancer
	std::vector<SpellType> spellbook;
	//entier permettant de savoir le moment où a été lancé le dernier sort
	unsigned int lastInvocationDate;
	// entier permettant de savoir le moment où a été recu le dernier sort
	unsigned int lastDammage;
	//chargement des sprites associées
	void loadSprites();
	// Récupère les évènements du joystick pour bouger le personnage
	void move(float x, float y);
	// Récupère les évenements du joystick pour incanter (ou pas) un sort
	Spell* invoque(float x, float y, bool A, bool B);

	std::string spriteName;


	// Constructeur du personnage, appellé au lancement de la partie (emplacement déterminé par init)
	Personnage(CharacterType type, int init, std::string spriteName);

public:
	// Méthode appellé lorsqu'un sort touche un personnage et qui met a jour les points de vie (et potentiellement la position) du personnage
	void receive(SpellType sort, sf::Vector2f spellPosition);
	// Getter de health 
	float getHealth();
	// Récupère les infos du Joystick et agit en fonction
	Spell* Action();
	//mise à jour des sprites
	bool updateSprites() override;
	//retourne un type (pour les collisions)
	std::string getType() override;
	//getter de player (numéro du joueur)
	int getNumber();
};