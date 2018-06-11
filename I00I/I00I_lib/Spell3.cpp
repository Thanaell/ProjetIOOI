#include "stdafx.h"
#include "Spell3.h"

Spell3::Spell3(b2Body* body, float x, float y, bool isFacingRight, int player) : Spell(SORT3, body, x, y, isFacingRight, player) {
	speed = 1;
}
