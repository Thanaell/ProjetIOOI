#pragma once
#include "stdafx.h"
#include "PlayingElement.h"
#include "SpellType.h"

class Spell : public PlayingElement {
	std::string name;
	SpellType type;
	double range; 
};