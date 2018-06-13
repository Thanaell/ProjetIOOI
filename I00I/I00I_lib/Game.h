#pragma once
#include "stdafx.h"
#include "Loader.h"
#include <Windows.h>
#include "MenuButton.h"
#include "constantes.h"
#include "Personnage.h"
#include "Spell.h"
#include "ContactListener.h"


/*
 * Classe Game :
 * Singleton et classe facade du jeux
 */
class Game {
	// Fenetre du programme
	sf::RenderWindow window;
	// Etat du programme (voir le diagramme de machine � �tat)
	GAME_STATE gameState;
	// Mutex qui couble l'ensemble de la fonction de chargement
	HANDLE loadMutex;
	// Mutex permettant � la gameloop de savoir quand afficher l'arri�re plan
	HANDLE loadMutexBackground;
	// Thread de chargement des assets, permettant de ne pas perturber la gameloop
	HANDLE loadThread;
	//	Pointeur sur le monde qui sera g�n�r� dans le jeu
	std::unique_ptr<b2World> world;
	MyContactListener myContactListenerInstance;

	///	Pour le menu
	// Arri�re plan a proprement parler
	std::unique_ptr<sf::Sprite> background;
	std::unique_ptr<sf::Sprite> playingBackground;
	sf::RectangleShape overBackground;
	std::unique_ptr<sf::Sprite> logo;
	// Liste des �l�ments (bouton) du menu
	std::vector<std::unique_ptr<MenuButton>> menuElements;

	std::vector<std::unique_ptr<Personnage>> players;
	std::vector<std::unique_ptr<Spell>> activeSpells;

	//valeurs pour le rafraichissement
	float timeStep;
	int velocityIterations;
	int positionIterations;

	int countFrame;
	bool isPlaying;

	static Game* _instance;
public:
	// Constructeur et seul m�thode publique
	static void CreateGame();
private:
	Game();
	// Fonction de gameloop : boucle infinie qui appelle les m�thodes de rafaichissement en fonction de l'�tat du jeu puis met a jour l'affichage
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

public:
	static b2World* getWorld();
	
};
