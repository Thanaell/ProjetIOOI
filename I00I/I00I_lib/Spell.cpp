#include "stdafx.h"
#include "Spell.h"
#include "Personnage.h"

// Constructeur du sort
Spell::Spell(SpellType myType) {
	type = myType;
}
// Fonction appel�e lors qu'un sort touche un personnage
void Spell::affect(Personnage &character) {
	character.receive(type);
}