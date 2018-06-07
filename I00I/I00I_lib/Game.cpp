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
	gameState(LOADING), timeStep(1.0f / 60.0f), velocityIterations(6), positionIterations(2)
{
//	Cr�ation des �l�ments de base du jeu

	// Cr�ation du mutex pour le chargement des donn�es
	loadMutex = NULL;

	// Cr�ation du thread de chargement
	DWORD threadID;
	loadThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) loading, this, 0, &threadID);
	assert(loadThread != NULL);
}

void Game::gameLoop() {
	//	Date du dernier affichage
	auto last = std::chrono::system_clock::now();

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
		auto endFrame = std::chrono::system_clock::now();

		//	on attend qu'il se soit bien passer le temps qu'il faut entre 2 frames
		int durationFrame = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - last).count();
		int timeToWait = FRAME_DURATION - durationFrame > 0 ? FRAME_DURATION - durationFrame : 0;
		Sleep(timeToWait);

		last = std::chrono::system_clock::now();
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
				//	une fois que le chargement des donn�es est termin�
				// On relache le thread et le mutex, et l'�tat du programme passe en "MENU"
			case WAIT_OBJECT_0:
				CloseHandle(loadMutexBackground);
				loadMutexBackground = NULL;
#ifdef DEBUG_LOG
				std::cout << "Le background a fini d'etre charg� : " << MS_SINCE_BEGIN << "ms" << std::endl;
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

	//	Le mutex n'a pas encore �t� cr�e par le thread
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
		//	une fois que le chargement des donn�es est termin�
		// On relache le thread et le mutex, et l'�tat du programme passe en "MENU"
	case WAIT_OBJECT_0:
		CloseHandle(loadThread);
		loadThread = NULL;
		CloseHandle(loadMutex);
		loadMutex = NULL;
#ifdef DEBUG_LOG
		std::cout << "Les donn�es ont finies d'etre charg�es et peuvent etre utilis�e : " << MS_SINCE_BEGIN << "ms" << std::endl;
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
		menuElements.push_back(std::unique_ptr<MenuButton>(new MenuButton(sf::Vector2f(.5f, .2f), sf::Vector2f(.4f, .15f), "Jouer !")));
	}


	// Gestion des �v�nements sur le menu
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
	for (auto& player : players) {
		Spell* newSpell = player->Action();
		if (newSpell != nullptr) {
#ifdef DEBUG_LOG
			std::cout << "Ajout d'un sort dans le monde : " << MS_SINCE_BEGIN << "ms" << std::endl;
			std::cout << "Il y a au total " << activeSpells.size() << " sorts dans le monde" << std::endl;
#endif
			activeSpells.push_back(std::unique_ptr<Spell>(newSpell));
		}
	}
	//	Calcul du monde
    world->Step(timeStep, velocityIterations, positionIterations);

	//	Gestion des collisions

	//	Affichage
	for (auto& p : players) {
		if (p->updateSprites())
			p->draw(window);
	}

	for (auto it = activeSpells.begin(); it != activeSpells.end();)
	{
		if (it->get()->updateSprites()) {
			it->get()->draw(window);
			++it;
		}
		else {
			it = activeSpells.erase(it);
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

void Game::createGame() {
	//Quatre coins de la zone (valeurs � ajuster)
	b2Vec2 v1(0.0f , 0.0f);
	b2Vec2 v2(0.0f, WORLD_HEIGHT);
	b2Vec2 v3(WORLD_WIDTH, 0.0f);
	b2Vec2 v4(WORLD_WIDTH, WORLD_HEIGHT);

	//cr�ation des 4 murs	
	//sol
	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	b2Body* sol = world->CreateBody(&bodyDef1);
	b2EdgeShape floor;
	floor.Set(v1, v3);
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
	rightwall.Set(v3, v4);
	b2FixtureDef fixtureDef3;
	fixtureDef3.shape = &rightwall;
	droite->CreateFixture(&fixtureDef3);

	//mur gauche
	b2BodyDef bodyDef4;
	bodyDef4.type = b2_staticBody;
	b2Body* gauche = world->CreateBody(&bodyDef4);
	b2EdgeShape leftwall;
	leftwall.Set(v1, v2);
	b2FixtureDef fixtureDef4;
	fixtureDef4.shape = &leftwall;
	gauche->CreateFixture(&fixtureDef4);
	
	//Personnages
	players.push_back(std::unique_ptr<Personnage>(new Personnage(TYPE1, 0)));
	players.push_back(std::unique_ptr<Personnage>(new Personnage(TYPE1, 1)));
}

void Game::gameOver() {
	players.clear();
	activeSpells.clear();
	delete world;
	world = nullptr;
	gameState = MENU;
}

DWORD Game::loading(LPVOID params) {
	Game* that = (Game*)params;
	// Cr�ation du mutex pour le chargement des donn�es
	that->loadMutex = CreateMutexA(NULL, FALSE, NULL);
	assert(that->loadMutex != NULL);
	auto mutexValue = WaitForSingleObject(that->loadMutex, 1);

	that->loadMutexBackground = CreateMutexA(NULL, FALSE, NULL);
	assert(that->loadMutexBackground != NULL);
	auto mutexValuebg = WaitForSingleObject(that->loadMutexBackground, 1);

	auto& sin = Loader::Instance();

	if (mutexValue == WAIT_OBJECT_0) {
		//	Chargement des donn�es
#ifdef DEBUG_LOG
		std::cout << "On est en train de charger des donn�es avec la fonction loading... : " << MS_SINCE_BEGIN << "ms" << std::endl;
#endif
		if (mutexValuebg == WAIT_OBJECT_0) {
			sin.loadFirst();
			ReleaseMutex(that->loadMutexBackground);
		}
		sin.loadLast();
		//Sleep(5000);
		//	Relache du mutex
		ReleaseMutex(that->loadMutex);
	}
	return 0;
}
 b2World * Game::getWorld() {
	return world;
}

