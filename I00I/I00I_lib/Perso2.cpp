#include "stdafx.h"
#include "Perso2.h"

Perso2::Perso2(int playerNumber) : Personnage(TYPE1, playerNumber, "wizard2") {
	vitesse = SPEED_PERSO_2;
	health.getObject()->setMaxValue(HEALTH_PERSO_2);
	health.getObject()->setValue(HEALTH_PERSO_2);
	spellbook.push_back(Cooldown<SpellType>(45, new SpellType(SORT1)));
	spellbook.push_back(Cooldown<SpellType>(75, new SpellType(SORT2)));
	spellbook.push_back(Cooldown<SpellType>(0, new SpellType(SORT3)));
}

