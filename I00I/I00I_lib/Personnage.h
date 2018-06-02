#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"
#include "CharacterType.h"
#include "Spell.h"

class Personnage : public PlayingElement {
	std::string name;
	int health;
	std::vector<SpellType> spellbook;
public:
	Personnage(CharacterType type);
	Spell& throwSpell(SpellType sort);
	void receive(SpellType sort);

};