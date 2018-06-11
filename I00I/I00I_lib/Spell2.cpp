#include "stdafx.h"
#include "Spell2.h"

Spell2::Spell2(b2Body* body, float x, float y, bool isFacingRight, int player) : Spell(SORT2, body, x, y, isFacingRight, player) {
	speed = 5;
}
