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
	HANDLE loadMutex;
	HANDLE loadThread;

	//	R�f�rence sur le monde qui sera g�n�r� dans le jeu
	b2World* world;
public :
	Game();
private:
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

	//	Fonction ex�cut�e sur un autre thread et qui charge en m�moire les donn�es du jeux, lache le s�maphore quand les donn�es sont charg�es
	static DWORD WINAPI loading(LPVOID);
};
