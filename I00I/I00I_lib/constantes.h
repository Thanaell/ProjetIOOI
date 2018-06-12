#pragma once

//	Define portant sur la fenetre au lancement du jeu
#define W_WIDTH (1280)
#define W_HEIGHT (720)
#define W_TITLE "Hello World!"

// Define portant sur la taille du monde box2D
#define WORLD_WIDTH (160)
#define WORLD_HEIGHT (90)


#define SPRITE_SCALE (sf::Vector2f(.2f, .2f))

// Définition de la taille des assets dessinés
#define HELTH_W_SIZE (W_WIDTH / 4.f)
#define HELTH_SIZE (sf::Vector2f(HELTH_W_SIZE, W_HEIGHT / 18.f))

// Constantes liées au jeu en lui meme
#define STICK_SENSIBILITY (20.f)
#define PLAYER_VELOCITY (2.5f)

// Path pour trouver les assests 
#define PATH_XML "..\\..\\data.xml"

// Constantes caractéristiques des différents personnages
#define HEALTH_PERSO_1 (100)
#define HEALTH_PERSO_2 (130)

// Constantes caractéristiques des différents sorts
#define SPEED_SORT_1 (20.f)
#define SPEED_SORT_2 (5.f)
#define SPEED_SORT_3 (1.f)

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

#define INVOCATION_RECOVERYTIME (600)

#define MS_SINCE_BEGIN clock()


#define COEF_SPELL_SPEED (19.f)