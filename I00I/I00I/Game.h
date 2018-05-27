#pragma once
#include "stdafx.h"

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)

enum GAME_STATE {
	LOADING,
	MENU,
	PLAYING,
	QUITTING
};

/*
 * Classe Game :
 * Singleton et classe facade du jeux
 */
class Game {
	sf::RenderWindow window;
	GAME_STATE gameState;

	//	R�f�rence sur le monde qui sera g�n�r� dans le jeu
	b2World* world;

public :
	Game();

};
