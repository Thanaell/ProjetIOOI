#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"

class Personnage : public PlayingElement {
	std::string name;
	int health;
	std::vector<SpellType> spellbook;
};