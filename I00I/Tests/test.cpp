#include "pch.h"
#include "../I00I_lib/Game.h"


TEST(Jeu, getWorld) {
	Game::getWorld();
}
TEST(Sort, Constructeur) {
	Personnage perso = Personnage(TYPE1);
	Spell sort = Spell(SORT1, perso.getBody());
	EXPECT_TRUE(1);
}
TEST(Sort, Affect) {
	Personnage perso = Personnage(TYPE1);
	Spell sort = Spell(SORT1,perso.getBody());
	sort.affect(perso);
	EXPECT_TRUE(perso.getHealth() == 90);
}