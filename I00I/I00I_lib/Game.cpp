#pragma once
#include "stdafx.h"
#include "Game.h"
#include <Windows.h>

Game* Game::_instance = NULL;
b2World* Game::world = new b2World(GRAVITY_WORLD);

void Game::CreateGame() {
	if (_instance == NULL) {
		_instance = new Game();
	}
	_instance->gameLoop();
}

Game::Game() :
	window(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE),
	gameState(LOADING)
{
//	Création des éléments de base du jeu

	// Création du mutex pour le chargement des données
	loadMutex = NULL;

	// Création du thread de chargement
	DWORD threadID;
	loadThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) loading, this, 0, &threadID);
	assert(loadThread != NULL);
}

void Game::gameLoop() {
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
	if (background.get() == NULL) {
		if (loadMutexBackground != NULL) {
			auto state = WaitForSingleObject(loadMutexBackground, 1);
			auto& sin = Loader::Instance();

			switch (state) {
			case WAIT_ABANDONED: break;
			case WAIT_TIMEOUT: break;
				//	une fois que le chargement des données est terminé
				// On relache le thread et le mutex, et l'état du programme passe en "MENU"
			case WAIT_OBJECT_0:
				CloseHandle(loadMutexBackground);
				loadMutexBackground = NULL;
#ifdef DEBUG_LOG
				std::cout << "Le background a fini d'etre chargé : " << clock() << std::endl;
#endif
				background.reset(new sf::Sprite(*sin.getTexture("background")));
				window.draw(*background.get());
				break;
			case WAIT_FAILED: break;
			}
		}
	}
	else {
		window.draw(*background.get());
	}

	//	Le mutex n'a pas encore été crée par le thread
	if (loadMutex == NULL) {
#ifdef DEBUG_LOG
		std::cout << "le mutex n'existe pas" << std::endl;
#endif
		return;
	}
	auto state = WaitForSingleObject(loadMutex, 1);
	switch (state) {
	case WAIT_ABANDONED: break;
	case WAIT_TIMEOUT: break;
		//	une fois que le chargement des données est terminé
		// On relache le thread et le mutex, et l'état du programme passe en "MENU"
	case WAIT_OBJECT_0:
		CloseHandle(loadThread);
		loadThread = NULL;
		CloseHandle(loadMutex);
		loadMutex = NULL;
#ifdef DEBUG_LOG
		std::cout << "Les données ont finies d'etre chargées et peuvent etre utilisée : " << clock() << std::endl;
#endif
		gameState = MENU;
		break;
	case WAIT_FAILED: break;
	default: break;
	}
	
	// Gestion des évènements durant le chargement
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
	// S'il le faut, on crée le menu
	if (menuElements.size() == 0) {
		menuElements.push_back(std::unique_ptr<MenuButton>(new MenuButton(sf::Vector2f(.5f, .2f), sf::Vector2f(.4f, .15f), "Jouer !")));
	}


	// Gestion des évènements sur le menu
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (menuElements[0]->isIn(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), window.getSize())) {
				menuElements.clear();
				//	Ici il faut constuire le monde avant de jouer
				createGame();
				//	On lance le jeu
				gameState = PLAYING;
#ifdef DEBUG_LOG
				std::cout << "Passage en mode jeu" << std::endl;
#endif
			}
			break;
		case sf::Event::Resized:
			/*for (auto &button : menuElements) {
				button.get()->resizeSprites(window.getSize());
			}*/
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}

	// On dessine le menu sur la fenetre
	if (background.get() != NULL) window.draw(*background.get());
	for (auto &shape : menuElements)
		shape->draw(window);
}

void Game::displayPlaying() {
	// Gestion des évènements durant le jeu
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
	// Gestion des évènements durant le déchargement
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

void Game::createGame() {
	//Quatre coins de la zone (valeurs à ajuster)
	b2Vec2 v1(0.0f, 0.0f);
	b2Vec2 v2(0.0f, 50.0f);
	b2Vec2 v3(100.0f, 0.0f);
	b2Vec2 v4(100.0f, 50.0f);
	//création des 4 murs	
	//sol
	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	b2Body* sol = world->CreateBody(&bodyDef1);
	b2EdgeShape floor;
	floor.Set(v1, v2);
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &floor;
	sol->CreateFixture(&fixtureDef1);

	//plafond
	b2BodyDef bodyDef2;
	bodyDef2.type = b2_staticBody;
	b2Body* plafond = world->CreateBody(&bodyDef2);
	b2EdgeShape ceiling;
	ceiling.Set(v2, v4);
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &ceiling;
	plafond->CreateFixture(&fixtureDef2);

	//mur droite
	b2BodyDef bodyDef3;
	bodyDef3.type = b2_staticBody;
	b2Body* droite = world->CreateBody(&bodyDef3);
	b2EdgeShape rightwall;
	ceiling.Set(v3, v4);
	b2FixtureDef fixtureDef3;
	fixtureDef3.shape = &rightwall;
	droite->CreateFixture(&fixtureDef3);

	//mur gauche
	b2BodyDef bodyDef4;
	bodyDef4.type = b2_staticBody;
	b2Body* gauche = world->CreateBody(&bodyDef4);
	b2EdgeShape leftwall;
	ceiling.Set(v1, v2);
	b2FixtureDef fixtureDef4;
	fixtureDef4.shape = &leftwall;
	gauche->CreateFixture(&fixtureDef4);
	
	
}

void Game::gameOver() {
}

DWORD Game::loading(LPVOID params) {
	Game* that = (Game*)params;
	// Création du mutex pour le chargement des données
	that->loadMutex = CreateMutexA(NULL, FALSE, NULL);
	assert(that->loadMutex != NULL);
	auto mutexValue = WaitForSingleObject(that->loadMutex, 1);

	that->loadMutexBackground = CreateMutexA(NULL, FALSE, NULL);
	assert(that->loadMutexBackground != NULL);
	auto mutexValuebg = WaitForSingleObject(that->loadMutexBackground, 1);

	auto& sin = Loader::Instance();

	if (mutexValue == WAIT_OBJECT_0) {
		//	Chargement des données
#ifdef DEBUG_LOG
		std::cout << "On est en train de charger des données avec la fonction loading... : " << clock() << std::endl;
#endif
		if (mutexValuebg == WAIT_OBJECT_0) {
			sin.loadFirst();
			ReleaseMutex(that->loadMutexBackground);
		}
		sin.loadLast();
		Sleep(5000);
		//	Relache du mutex
		ReleaseMutex(that->loadMutex);
	}
	return 0;
}
 b2World * Game::getWorld() {
	return world;
}

