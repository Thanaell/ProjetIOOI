#include "stdafx.h"
#include "Spell.h"

// Constructeur du sort
Spell::Spell(SpellType type) {

}
// Fonction appelé lors qu'un sort touche un personnage
void Spell::affect(Personnage& character) {
	character.receive(type);
}