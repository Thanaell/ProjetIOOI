#pragma once
#include "stdafx.h"
#include "SpellType.h"
#include "Spell.h"


class Spell3 : public Spell {

public:
	Spell3(b2Body* body, float x, float y, bool isFacingRight, int player);
};