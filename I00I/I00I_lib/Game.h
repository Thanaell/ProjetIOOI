#pragma once
#include "stdafx.h"
#include "Loader.h"
#include <Windows.h>
#include "MenuButton.h"
#include "constantes.h"
#include "Personnage.h"
#include "Spell.h"



/*
 * Classe Game :
 * Singleton et classe facade du jeux
 */
class Game {
	// Fenetre du programme
	sf::RenderWindow window;

	// Etat du programme (voir le diagramme de machine à état)
	GAME_STATE gameState;

	// Mutex qui couble l'ensemble de la fonction de chargement
	HANDLE loadMutex;
	// Mutex permettant à la gameloop de savoir quand afficher l'arrière plan
	HANDLE loadMutexBackground;
	// Thread de chargement des assets, permettant de ne pas perturber la gameloop
	HANDLE loadThread;

	//	Pointeur sur le monde qui sera généré dans le jeu
	std::unique_ptr<b2World> world;

	///	Pour le menu
	// Arrière plan a proprement parler
	std::unique_ptr<sf::Sprite> background;
	// Liste des éléments (bouton) du menu
	std::vector<std::unique_ptr<MenuButton>> menuElements;


	static Game* _instance;
public:
	// Constructeur et seul méthode publique
	static void CreateGame();
private:
	Game();
	// Fonction de gameloop : boucle infinie qui appelle les méthodes de rafaichissement en fonction de l'état du jeu puis met a jour l'affichage
	void gameLoop();

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

	//	Fonction qui instancie les données nécessaires pour la partie
	void createGame();

	void gameOver();

	//	Fonction exécutée sur un autre thread et qui charge en mémoire les données du jeux, lache le sémaphore quand les données sont chargées
	static DWORD WINAPI loading(LPVOID);

public:
	static b2World& getWorld();
};
