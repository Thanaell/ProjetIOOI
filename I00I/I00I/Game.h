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

	//	Référence sur le monde qui sera généré dans le jeu
	b2World* world;
public :
	Game();
private:
	//Méthodes de rafraichissement de l'affichage en fonction de l'état du programme
	// Chaque méthode est amenée à etre appelée en boucle, a chaque rafraichissement de l'affichage
	// Jusqu'à ce que la classe change d'état

	//	Fonction qui affiche quelque chose pendant le chargement des données/assets en mémmoire (ce chargement est fait sur un autre thread)
	void displayLoading();

	//	Fonction qui affiche et fait réagit le menu et les paramétrages de partie
	void displayMenu();

	//	Fonction qui gère la partie
	void displayPlaying();

	//	Fonction qui s'assure qu'on ne perd aucune données avant de quitter
	void displayUnLoading();

	//	Fonction exécutée sur un autre thread et qui charge en mémoire les données du jeux, lache le sémaphore quand les données sont chargées
	static DWORD WINAPI loading(LPVOID);
};
