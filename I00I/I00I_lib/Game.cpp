#pragma once
#include "stdafx.h"
#include "Game.h"
#include <Windows.h>

Game* Game::_instance = NULL;


void Game::CreateGame() {
	if (_instance == NULL) {
		_instance = new Game();
	}
	_instance->gameLoop();
}

Game::Game() :
	countFrame(0), isPlaying(false),
	window(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE),
	gameState(LOADING), timeStep(1.0f / 60.0f), velocityIterations(6), positionIterations(2),
	overBackground(sf::RectangleShape(sf::Vector2f(W_WIDTH, W_HEIGHT)))
{
//	Cr�ation des �l�ments de base du jeu

	// Cr�ation du mutex pour le chargement des donn�es
	loadMutex = NULL;

	// Cr�ation du thread de chargement
	DWORD threadID;
	loadThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) loading, this, 0, &threadID);
	assert(loadThread != NULL);

	// Ajouté a visée de test dans le but de changer la gestion des threads
	Sleep(200);
}

void Game::gameLoop() {
	//	Date du dernier affichage
	auto last = std::chrono::system_clock::now();
	bool frameDelayed = false;

	//	Boucle de d'affichage de la fenetre
	while (window.isOpen()) {
		if (!frameDelayed) {
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
		}
		window.display();
		auto endFrame = std::chrono::system_clock::now();

		countFrame++;

		//	on attend qu'il se soit bien passer le temps qu'il faut entre 2 frames
		_int64 durationFrame = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - last).count();
		frameDelayed = FRAME_DURATION - durationFrame < 0;
		DWORD timeToWait = FRAME_DURATION - durationFrame > 0 ? FRAME_DURATION - durationFrame : 0;
		Sleep(timeToWait);

		last = std::chrono::system_clock::now();
	}
}

void Game::displayLoading() {
	auto& sin = Loader::Instance();
	if (background.get() == NULL) {
		if (loadMutexBackground != NULL) {
			auto state = WaitForSingleObject(loadMutexBackground, 1);

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
				overBackground.setFillColor(sf::Color(0x000000A9));
				logo.reset(new sf::Sprite(*sin.getTexture("logo")));
				window.draw(*logo.get());
				break;
			case WAIT_FAILED: break;
			}
		}
	}
	else {
		window.draw(*logo.get());
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
		logo->setOrigin(640.f, 360.f);
		logo->setScale(.4f, .4f);
		logo->setPosition(680.f, 580.f);
		playingBackground.reset(new sf::Sprite(*sin.getTexture("playing_background")));
		spriteGameOver.reset(new sf::Sprite(*sin.getTexture("gameover")));
		spriteGameOver->setOrigin(GAMEOVER_ORIGINE);
		spriteGameOver->setPosition(GAMEOVER_POSITION);
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
		menuElements.push_back(std::unique_ptr<MenuButton>(new MenuButton(sf::Vector2f(.5f, .2f), "Play", true)));
		menuElements.push_back(std::unique_ptr<MenuButton>(new MenuButton(sf::Vector2f(.5f, .4f), "Exit")));
	}


	// Gestion des �v�nements sur le menu
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (menuElements[0]->isIn(sf::Vector2u(event.mouseButton.x, event.mouseButton.y), window.getSize())) {
				menuElements.clear();
				//	Ici il faut constuire le monde avant de jouer
				createGame();
				//	On lance le jeu
				gameState = PLAYING;
			}
			else if (menuElements[1]->isIn(sf::Vector2u(event.mouseButton.x, event.mouseButton.y), window.getSize())) {
				window.close();
			}
			break;
		case sf::Event::JoystickButtonPressed:
			if (event.joystickMove.joystickId == 0) {
				if (event.joystickButton.button == 0) {
					if (menuElements[0]->getState()) {
						menuElements.clear();
						//	Ici il faut constuire le monde avant de jouer
						createGame();
						//	On lance le jeu
						gameState = PLAYING;
					}
					else if (menuElements[1]->getState()) {
						window.close();
					}
				}
			}
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Return) {
				if (menuElements[0]->getState()) {
					menuElements.clear();
					//	Ici il faut constuire le monde avant de jouer
					createGame();
					//	On lance le jeu
					gameState = PLAYING;
				}
				else if (menuElements[1]->getState()) {
					window.close();
				}
			}
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
	if (countFrame % 10 == 0 && abs(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)) > 80) {
		for (auto & b : menuElements) b->changeSelection();
	}

	// On dessine le menu sur la fenetre
	if (background.get() != NULL) window.draw(*background.get());
	window.draw(overBackground);
	if (logo.get() != NULL) window.draw(*logo.get());
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
			case sf::Event::JoystickButtonPressed:
				if (event.joystickButton.button == 6) {
					gameOver();
					return;
				}
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					gameOver();
					return;
				}
			default:
				break;
		}
	}

	if(isPlaying) {
		for (auto& e : gameElements) {
			PlayingElement* newElement = e->action();
			if (newElement != nullptr) {
				buffer.push_back(newElement);
			}
		}
		for (auto ne : buffer) {
			gameElements.push_back(std::unique_ptr<PlayingElement>(ne));
		}

		buffer.clear();

		//	Calcul du monde
		world->Step(timeStep, velocityIterations, positionIterations);

		//	Gestion des collisions et du gameover
		for (auto it = gameElements.begin(); it != gameElements.end();) {
			if (it->get()->isToDestroy() == true) {
				it = gameElements.erase(it);
			}
			else {
				if(it->get()->getHealth() <= 0) {
					isPlaying = false;
					std::cout << "le personnage " << it->get()->getNumber() << " est mort";
				}
				++it;
			}
		}
	}

	//	Affichage
	window.draw(*playingBackground.get());


	for (auto it = gameElements.begin(); it != gameElements.end();) {
		if (it->get()->updateSprites()) {
			it->get()->draw(window);
			++it;
		}
		else {
			it = gameElements.erase(it);
		}
	}
	
	
	if(!isPlaying) {
		window.draw(*spriteGameOver.get());
		if(sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			gameOver();
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
	isPlaying = true;
	world.reset(new b2World(GRAVITY_WORLD));

	//contact listener
	world->SetContactListener(&myContactListenerInstance);
	//Quatre coins de la zone 
	b2Vec2 v1(0.0f , 0.0f);
	b2Vec2 v2(0.0f, WORLD_HEIGHT);
	b2Vec2 v3(WORLD_WIDTH, 0.0f);
	b2Vec2 v4(WORLD_WIDTH, WORLD_HEIGHT);

	//cr�ation des 4 murs	
	//sol
	walls.push_back(std::unique_ptr<Wall>(new Wall(v1, v3)));

	//plafond
	walls.push_back(std::unique_ptr<Wall>(new Wall(v2, v4)));

	//mur droite
	walls.push_back(std::unique_ptr<Wall>(new Wall(v3, v4)));

	//mur gauche
	walls.push_back(std::unique_ptr<Wall>(new Wall(v1, v2)));
	
	//Personnages
	gameElements.push_back(std::unique_ptr<Personnage>(Personnage::createPersonnage(TYPE2, 0)));
	gameElements.push_back(std::unique_ptr<Personnage>(Personnage::createPersonnage(TYPE1, 1)));
}

void Game::gameOver() {
	gameElements.clear();
	walls.clear();
	world.reset(nullptr);
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
		//	Relache du mutex
		ReleaseMutex(that->loadMutex);
	}
	return 0;
}

b2World * Game::getWorld() {
	return _instance->world.get();
}

int Game::getFrameNumber() {
	return _instance->countFrame;
}

