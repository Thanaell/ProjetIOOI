#include "pch.h"
#include "../I00I_lib/Game.h"


TEST(Sort, Constructeur) {
	Personnage perso = Personnage(TYPE1,0);
	Spell sort = Spell(SORT1, perso.getBody(),1,1);
	EXPECT_TRUE(1);
}
TEST(Sort, Affect) {
	Personnage perso = Personnage(TYPE1,0);
	Spell sort = Spell(SORT1,perso.getBody(),1,1);
	sort.affect(perso);
	EXPECT_TRUE(perso.getHealth() == 90);
}
TEST(Jeu, getWorld) {
	Game::getWorld();
}