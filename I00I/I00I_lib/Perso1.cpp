#include "stdafx.h"
#include "Perso1.h"

Perso1::Perso1(int playerNumber) : Personnage(TYPE1, playerNumber, "wizard1") {
	vitesse = PLAYER_VELOCITY;
	maxHealth = HEALTH_PERSO_1;
	spellbook.push_back(SORT1);
	spellbook.push_back(SORT2);
	spellbook.push_back(SORT3);
	health = maxHealth;
}
