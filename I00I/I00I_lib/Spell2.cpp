#include "stdafx.h"
#include "Spell2.h"

void Spell2::movingStrategy() {
	float vitesseLineaire = SPEED_SORT_2 * COEF_SPELL_SPEED;

	b2Vec2 vitesse(vitesseLineaire * std::cos(theta) + vitesseLineaire * std::cos(.2f * lifeTime) * std::sin(theta),
				   vitesseLineaire * std::sin(theta) - vitesseLineaire * std::cos(.2f * lifeTime) * std::cos(theta));
	body->SetLinearVelocity(vitesse);
}

Spell2::Spell2(b2Body* body, float x, float y, bool isFacingRight, int player) : Spell(SORT2, body, x, y, isFacingRight, player) {
	power = POWER_SORT_2;
}
