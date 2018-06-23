#include "stdafx.h"
#include "Perso1.h"

Perso1::Perso1(int playerNumber) : Personnage(TYPE1, playerNumber, "wizard1") {
	vitesse = SPEED_PERSO_1;
	health.setMaxValue(HEALTH_PERSO_1);
	health.setValue(HEALTH_PERSO_1);
	spellbook.push_back(SORT1);
	spellbook.push_back(SORT2);
	spellbook.push_back(SORT3);
}
