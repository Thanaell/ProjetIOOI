#pragma once
#include "stdafx.h"
#include <Windows.h>
#include "MenuButton.h"
#include "constantes.h"



/*
 * Classe Game :
 * Singleton et classe facade du jeux
 */
class Game {
	sf::RenderWindow window;
	GAME_STATE gameState;
	HANDLE loadMutex;
	HANDLE loadMutexBackground;
	HANDLE loadThread;

	//	R�f�rence sur le monde qui sera g�n�r� dans le jeu
	std::unique_ptr<b2World> world;

	//	Pour le menu
	sf::Texture backgroundTexture;
	std::unique_ptr<sf::Sprite> background;
	std::vector<std::unique_ptr<MenuButton>> menuElements;
public:
	Game();
private:
	void gameLoop();

	//M�thodes de rafraichissement de l'affichage en fonction de l'�tat du programme
	// Chaque m�thode est amen�e � etre appel�e en boucle, a chaque rafraichissement de l'affichage
	// Jusqu'� ce que la classe change d'�tat

	//	Fonction qui affiche quelque chose pendant le chargement des donn�es/assets en m�mmoire (ce chargement est fait sur un autre thread)
	void displayLoading();

	//	Fonction qui affiche et fait r�agit le menu et les param�trages de partie
	void displayMenu();

	//	Fonction qui g�re la partie
	void displayPlaying();

	//	Fonction qui s'assure qu'on ne perd aucune donn�es avant de quitter
	void displayUnLoading();

	//	Fonction qui instancie les donn�es n�cessaires pour la partie
	void createGame();

	void gameOver();

	//	Fonction ex�cut�e sur un autre thread et qui charge en m�moire les donn�es du jeux, lache le s�maphore quand les donn�es sont charg�es
	static DWORD WINAPI loading(LPVOID);
};
