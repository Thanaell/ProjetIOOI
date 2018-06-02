#include "stdafx.h"
#include "Personnage.h"

//Constructeur selon un arch�type (TODO: autres arch�types)
Personnage::Personnage(CharacterType type) {
	switch (type) {
	case TYPE1:
		health = 100;
		spellbook.push_back(SORT1);
		break;
	}
}

void Personnage::receive(SpellType sort) {
	switch (sort) {
	case TYPE1:
		health -= 10;
		break;
	}
}

int Personnage::getHealth() {
	return health;
}