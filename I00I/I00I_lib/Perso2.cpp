#include "stdafx.h"
#include "Perso2.h"

Perso2::Perso2(int playerNumber) : Personnage(TYPE1, playerNumber, "wizard2") {
	vitesse = SPEED_PERSO_2;
	health.setMaxValue(HEALTH_PERSO_2);
	health.setValue(HEALTH_PERSO_2);
	spellbook.push_back(SORT1);
	spellbook.push_back(SORT2);
	spellbook.push_back(SORT3);
}

