#include "stdafx.h"
#include "Perso2.h"

Perso2::Perso2(int playerNumber) : Personnage(TYPE1, playerNumber, "wizard2") {
	vitesse = 0.8 * PLAYER_VELOCITY;
	maxHealth = 130;
	spellbook.push_back(SORT1);
	spellbook.push_back(SORT2);
	spellbook.push_back(SORT3);
	health = maxHealth;
}

