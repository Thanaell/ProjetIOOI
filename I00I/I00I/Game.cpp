#pragma once
#include "stdafx.h"
#include "Game.h"

Game::Game() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hello World"),
	world(NULL),
	gameState(LOADING)
{
	int a;
	//	Cr�ation des �l�ments de base du jeu

	//	Boucle de d'affichage de la fenetre
	while (window.isOpen()) {
		switch (gameState) {
		case LOADING: break;
		case MENU: break;
		case PLAYING: break;
		case QUITTING: break;
		}
		window.display();
	}
	std::cin >> a;
}

