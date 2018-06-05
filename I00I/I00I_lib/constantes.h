#pragma once

//	Define portant sur la fenetre au lancement du jeu
#define W_WIDTH (1000)
#define W_HEIGHT (1000)
#define W_TITLE "Hello World!"

//	Path pour trouver les assests (a terme il n'y aura que le path pour trouver le xml)
#define PATH_XML "..\\..\\data.xml"

//	Enumération des états du programme au cours de sa vie (voir le diagramme de machine a état)
enum GAME_STATE {
	LOADING,
	MENU,
	PLAYING,
	QUITTING
};

//	Constantes liées au jeu lui meme
#define GRAVITY_WORLD (b2Vec2(0.f, 1.f))

#define FRAME_DURATION (1000/60)

