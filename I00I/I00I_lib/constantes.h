#pragma once
#define W_HEIGHT (720)

// Ratios utiles
#define RATIO_WINDOWS_B2D (8.f)
#define RATIO_SCREEN_X (16.f)
#define RATIO_SCREEN_Y (9.f)
#define RATIO_SCREEN (RATIO_SCREEN_X/RATIO_SCREEN_Y)

//	Define portant sur la fenetre au lancement du jeu
#define W_WIDTH (W_HEIGHT * RATIO_SCREEN)
#define W_TITLE "Hello World!"

// Define portant sur la taille du monde box2D
#define WORLD_WIDTH (W_WIDTH / RATIO_WINDOWS_B2D)
#define WORLD_HEIGHT (W_HEIGHT / RATIO_WINDOWS_B2D)


// Constantes liées à SFML
#define SPRITE_SCALE (sf::Vector2f(.2f, .2f))
#define SPELL_SPRITE_ORIGINE (sf::Vector2f(100.f, 100.f))
#define PLAYER_SPRITE_ORIGINE (sf::Vector2f(200.f, 200.f))

// Définition de la taille des assets dessinés
#define HELTH_W_SIZE (W_WIDTH / 4.f)
#define HELTH_SIZE (sf::Vector2f(HELTH_W_SIZE, W_HEIGHT / 18.f))
#define HEALTH_ORIGINE(x) (sf::Vector2f(x == 0 ? 0.f: HELTH_W_SIZE, 0.f))
#define HEALTH_POSITION(x) (sf::Vector2f(x == 0 ? 50.f : W_WIDTH - 50.f, 50.f))
#define HEALTH_COLOR (sf::Color::Color(0xe040109a))

// Constantes et macro liées au jeu en lui meme
#define STICK_SENSIBILITY (20.f)
#define KEYBOARD_ACTION (50.f)

// Constantes et macros liées a Box2D
#define PLAYER_VELOCITY (2.5f)
#define PLAYER_POSITION_X(x) ((x == 0 ? 1 : 7) * WORLD_WIDTH / 8)
#define PLAYER_POSITION_Y (WORLD_HEIGHT / 5)
#define PLAYER_DENSITY (1.f)
#define PLAYER_FRICTION (.3f)
#define PLAYER_SIZE_B2D_X (WORLD_WIDTH / (RATIO_SCREEN_X * 2.f))
#define PLAYER_SIZE_B2D_Y (WORLD_WIDTH / (RATIO_SCREEN_Y * 2.f))
#define SPELL_SIZE_B2D (WORLD_HEIGHT / (RATIO_SCREEN_X * 4.f))

// Path pour trouver les assests 
#define PATH_XML "..\\..\\data.xml"

// Constantes caractéristiques des différents personnages
#define HEALTH_PERSO_1 (100)
#define HEALTH_PERSO_2 (130)

// Constantes caractéristiques des différents sorts
#define SPEED_SORT_1 (20.f)
#define SPEED_SORT_2 (5.f)
#define SPEED_SORT_3 (1.f)

//	Enumération des états du programme au cours de sa vie (voir le diagramme de machine a état)
enum GAME_STATE {
	LOADING,
	MENU,
	PLAYING,
	QUITTING
};

//	Constantes liées au jeu lui meme
#define GRAVITY_WORLD (b2Vec2(0.f, -100.f))

#define FRAME_DURATION (1000/60)

#define INVOCATION_RECOVERYTIME (600)

#define MS_SINCE_BEGIN clock()


#define COEF_SPELL_SPEED (19.f)