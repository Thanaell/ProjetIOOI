#include "stdafx.h"
#include "Perso1.h"

Perso1::Perso1(int playerNumber) : Personnage(TYPE1, playerNumber, "wizard1") {
	vitesse = SPEED_PERSO_1;
	health.getObject()->setMaxValue(HEALTH_PERSO_1);
	health.getObject()->setValue(HEALTH_PERSO_1);
	spellbook.push_back(Cooldown<SpellType>(45, new SpellType(SORT1)));
	spellbook.push_back(Cooldown<SpellType>(75, new SpellType(SORT2)));
	spellbook.push_back(Cooldown<SpellType>(0, new SpellType(SORT3)));
}
