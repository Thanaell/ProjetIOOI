#pragma once
#include "stdafx.h"
#include "Game.h"
#include <Windows.h>

#define ISBETWEEN(x,a,b) ((x >= a) && (x <= b))

Game::Game() :
	window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Hello World"),
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
		window.clear();
		switch (gameState) {
		case LOADING: 
			displayLoading();
			break;
		case MENU: 
			displayMenu();
			break;
		case PLAYING: 
			displayPlaying();
			break;
		case QUITTING: 
			displayPlaying();
			break;
		}
		window.display();
	}

}

void Game::displayLoading() {
	//	Le mutex n'a pas encore �t� cr�e par le thread
	if (loadMutex == NULL) {
#ifdef DEBUG_LOG
		std::cout << "le mutex n'existe pas" << std::endl;
#endif
		return;
	}
	auto state = WaitForSingleObject(loadMutex, 10);
	switch (state) {
	case WAIT_ABANDONED: break;
	case WAIT_TIMEOUT: break;
		//	une fois que le chargement des donn�es est termin�
		// On relache le thread et le mutex, et l'�tat du programme passe en "MENU"
	case WAIT_OBJECT_0:
		CloseHandle(loadThread);
		loadThread = NULL;
		CloseHandle(loadMutex);
		loadMutex = NULL;
#ifdef DEBUG_LOG
		std::cout << "Les donn�es ont finies d'etre charg�es et peuvent etre utilis�e" << std::endl;
#endif
		gameState = MENU;
		break;
	case WAIT_FAILED: break;
	default: break;
	}
	
	// Gestion des �v�nements durant le chargement
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			//	Si l'utilisateur quitte l'application pendant le chargement
			//	Il faut mettre fin au thread de chargement avant de quitter l'application
			if (loadThread != NULL) {
				DWORD dwExit;
				GetExitCodeThread(loadThread, &dwExit);
				TerminateThread(loadThread, dwExit);
				CloseHandle(loadThread);
				loadThread = NULL;
				if (loadMutex != NULL) {
					CloseHandle(loadMutex);
					loadMutex = NULL;
				}
			}
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::displayMenu() {
	// S'il le faut, on cr�e le menu
	if (menuElements.size() == 0) {
		std::unique_ptr<sf::RectangleShape> bouton(new sf::RectangleShape(sf::Vector2f(200.f, 50.f)));
		bouton->setPosition(sf::Vector2f(400.f, 200.f));
		bouton->setFillColor(sf::Color::Red);
		menuElements.push_back(std::move(bouton));
	}

	// Gestion des �v�nements sur le menu
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (ISBETWEEN(event.mouseButton.x, 400, 600) && ISBETWEEN(event.mouseButton.y, 200, 250)) {
				menuElements.clear();
				gameState = PLAYING;
#ifdef DEBUG_LOG
				std::cout << "Passage en mode jeu" << std::endl;
#endif
			}
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}

	// On dessine le menu sur la fenetre
	for (auto &shape : menuElements)
		window.draw(*shape);
}

void Game::displayPlaying() {
	// Gestion des �v�nements durant le jeu
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::displayUnLoading() {
	// Gestion des �v�nements durant le d�chargement
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
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
		Sleep(5000);
		//	Relache du mutex
		ReleaseMutex(that->loadMutex);
	}
	return 0;
}

