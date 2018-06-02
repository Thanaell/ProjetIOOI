#include "pch.h"
#include "../I00I_lib/Game.h"

TEST(Sort, Affect) {
	Personnage perso = Personnage(TYPE1);
	Spell sort = Spell(SORT1);
	sort.affect(perso);
	EXPECT_TRUE(perso.getHealth() == 90);
}