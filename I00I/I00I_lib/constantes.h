#pragma once

//	Define portant sur la fenetre au lancement du jeu
#define W_WIDTH (1280)
#define W_HEIGHT (720)
#define W_TITLE "Hello World!"

//Define portant sur la taille du monde box2D
#define WORLD_WIDTH (160)
#define WORLD_HEIGHT (90)

#define SPRITE_SCALE (sf::Vector2f(.2f, .2f))
#define STICK_SENSIBILITY (20.f)
#define PLAYER_VELOCITY (2.5f)


//	Path pour trouver les assests 
#define PATH_XML "..\\..\\data.xml"

//	Enumération des états du programme au cours de sa vie (voir le diagramme de machine a état)
enum GAME_STATE {
	LOADING,
	MENU,
	PLAYING,
	QUITTING
};

//	Constantes liées au jeu lui meme
#define GRAVITY_WORLD (b2Vec2(0.f, -100.f))

#define FRAME_DURATION (1000/60)

#define INVOCATION_RECOVERYTIME (1000)

#define MS_SINCE_BEGIN clock()

