#pragma once
#include "stdafx.h"
#include "SpellType.h"
#include "Spell.h"


class Spell2 : public Spell {

public:
	Spell2(b2Body* body, float x, float y, bool isFacingRight, int player);
};