#pragma once
#include "stdafx.h"
#include "Game.h"

Game::Game() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hello World"),
	world(NULL),
	gameState(LOADING)
{
//	Cr�ation des �l�ments de base du jeu

	// Cr�ation du mutex pour le chargement des donn�es
	loadMutex = NULL;

	// Cr�ation du thread de chargement
	DWORD threadID;
	loadThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) loading, this, 0, &threadID);
	assert(loadThread != NULL);

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

}

void Game::displayLoading() {
	//	Le mutex n'a pas encore �t� cr�e par le thread
	if (loadMutex == NULL) return;
	auto state = WaitForSingleObject(loadMutex, 10);
	switch (state) {
	case WAIT_ABANDONED: break;
	case WAIT_TIMEOUT: break;
		//	une fois que le chargement des donn�es est termin�
		// On relache le thread et le mutex, et l'�tat du programme passe en "MENU"
	case WAIT_OBJECT_0:
		CloseHandle(loadThread);
		CloseHandle(loadMutex);
		gameState = MENU;
		break;
	case WAIT_FAILED: break;
	default: break;
	}
}

DWORD Game::loading(LPVOID params) {
	Game* that = (Game*)params;
	// Cr�ation du mutex pour le chargement des donn�es
	that->loadMutex = CreateMutexA(NULL, FALSE, NULL);
	assert(that->loadMutex != NULL);
	auto mutexValue = WaitForSingleObject(that->loadMutex, 1);
	if (mutexValue == WAIT_OBJECT_0) {
		//	Chargement des donn�es
#ifdef DEBUG_LOG
		std::cout << "On est en train de charger des donn�es avec la fonction loading..." << std::endl;
#endif
		//	Relache du mutex
		ReleaseMutex(that->loadMutex);
	}
	return 0;
}

