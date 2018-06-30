#include "stdafx.h"
#include "Spell1.h"

void Spell1::movingStrategy() {
	((b2CircleShape*)body->GetFixtureList()->GetShape())->m_radius *= 1.02f;
}

Spell1::Spell1(b2Body* body, float x, float y, bool isFacingRight, int player) : Spell(SORT1,body, x,y,isFacingRight,player) {
	power = POWER_SORT_1;
}
