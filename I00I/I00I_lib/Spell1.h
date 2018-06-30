#pragma once
#include "stdafx.h"
#include "SpellType.h"
#include "Spell.h"


class Spell1 : public Spell {

	void movingStrategy() override;
public:
	Spell1(b2Body* body, float x, float y, bool isFacingRight, int player);
};