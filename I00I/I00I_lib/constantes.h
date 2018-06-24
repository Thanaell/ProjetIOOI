#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SpellType.h"
#include "CharacterType.h"

// Constante indépendante fixant la hauteur de la fenetre 
static const float W_HEIGHT(720);

// Ratios utiles permettant de définir comment Box2d et SFML interagissent entre eux
static const float RATIO_WINDOWS_B2D(8.f);
static const float RATIO_SCREEN_X(16.f);
static const float RATIO_SCREEN_Y(9.f);
static const float RATIO_SCREEN(RATIO_SCREEN_X / RATIO_SCREEN_Y);

//	Define portant sur la fenetre au lancement du jeu
static const float W_WIDTH(W_HEIGHT * RATIO_SCREEN);
static const std::string W_TITLE("Hello World!");

// Define portant sur la taille du monde box2D
static const float WORLD_WIDTH(W_WIDTH / RATIO_WINDOWS_B2D);
static const float WORLD_HEIGHT(W_HEIGHT / RATIO_WINDOWS_B2D);
static const b2Vec2 GRAVITY_WORLD(0.f, -10.f);

enum ORIGINE {
	TOPLEFT, BOTTOMLEFT, TOPRIGHT, BOTTOMRIGHT, CENTER
};

// Constantes liées à SFML
static const sf::Vector2f SPRITE_SCALE(.2f, .2f);
static const sf::Vector2f SPELL_SPRITE_ORIGINE(100.f, 100.f);
static const sf::Vector2f PLAYER_SPRITE_ORIGINE(200.f, 200.f);
static const float BUTTON_SIZE_X(320.f);
static const float BUTTON_SIZE_Y(108.f);
static const sf::Vector2f BUTTON_ORIGINE(BUTTON_SIZE_X / 2, BUTTON_SIZE_Y / 2);
static const sf::Vector2f BUTTON_POSITION(sf::Vector2f p) { return sf::Vector2f(p.x * W_WIDTH, p.y * W_HEIGHT); }
static const sf::Vector2f SELECT_BUTTON_SIZE(BUTTON_SIZE_X + 10.f, BUTTON_SIZE_Y + 6.f);
static const sf::Vector2f SELECT_BUTTON_ORIGINE ((BUTTON_SIZE_X + 10.f) / 2, (BUTTON_SIZE_Y + 6.f) / 2);
static const sf::Color SELECT_BUTTON_COLOR(0x9a9a10FF);
static const float INTERFACE_PLAYER_SIZE_X(326.f);
static const float INTERFACE_PLAYER_SIZE_Y(46.f);
static const sf::Vector2f GAMEOVER_ORIGINE(W_WIDTH / 2, W_HEIGHT / 2);
static const sf::Vector2f GAMEOVER_POSITION(W_WIDTH / 2, W_HEIGHT / 2);

// Définition de la taille des assets dessinés
static const float HELTH_W_SIZE(W_WIDTH / 4.f);
static const sf::Vector2f HELTH_SIZE(HELTH_W_SIZE, W_HEIGHT / 18.f);
static const sf::Vector2f HEALTH_POSITION(int x) { return sf::Vector2f(x == 0 ? 50.f : W_WIDTH - 50.f, 50.f); }
static const sf::Color HEALTH_COLOR(0xe040109a);
static const sf::Vector2f SHIELD_GAUGE_SIZE(W_HEIGHT / 2, 15.f);
static const sf::Vector2f SHIELD_GAUGE_POSITION(int x) { return sf::Vector2f(x == 0 ? 2.f : W_WIDTH - 2.f, W_HEIGHT - 2.f); }
static const sf::Color SHIELD_GAUGE_COLOR(0x1850c39a);
static const sf::Vector2f ABSORBING_GAUGE_SIZE(HELTH_W_SIZE, W_HEIGHT / 36.f);
static const sf::Vector2f ABSORBING_GAUGE_POSITION(int x) { return sf::Vector2f(x == 0 ? 50.f : W_WIDTH - 50.f, 95.f); }
static const sf::Color ABSORBING_GAUGE_COLOR(0xe0a0359a);

// Constantes et macro liées au jeu en lui meme
static const float STICK_SENSIBILITY(20.f);
static const float KEYBOARD_ACTION(50.f);

// Constantes et macros liées a Box2D
static const float PLAYER_VELOCITY(2.5f);
static const float PLAYER_INERTIE(5.5f);
static const float PLAYER_POSITION_X(int x) { return (x == 0 ? 1 : 7) * WORLD_WIDTH / 8; }
static const float PLAYER_POSITION_Y(WORLD_HEIGHT / 5);
static const float PLAYER_DENSITY(1.f);
static const float PLAYER_FRICTION(.3f);
static const float PLAYER_SIZE_B2D_X(WORLD_WIDTH / (RATIO_SCREEN_X * 2.f));
static const float PLAYER_SIZE_B2D_Y(WORLD_WIDTH / (RATIO_SCREEN_Y * 2.f));
static const float SPELL_SIZE_B2D(WORLD_HEIGHT / (RATIO_SCREEN_X * 4.f));

// Path pour trouver les assests 
static const char* PATH_XML = "..\\..\\data.xml";

// Constantes caractéristiques des différents personnages
static const float HEALTH_PERSO_1(100);
static const float HEALTH_PERSO_2(130);
static const float SPEED_PERSO_1(PLAYER_VELOCITY);
static const float SPEED_PERSO_2(PLAYER_VELOCITY * .8f);
static const float DAMMAGE_SPRITE_DURATION(4);
static const int PROTECTION_DURATION(150);	// indiqué en nombre de frames de protection
static const int ABSORPTION_DURATION(20);	// indiqué en nombre de frames d'absorption
static const int ABSORPTION_NEEDED(100);	// indiqué en nombre de frames de protection

// Constantes caractéristiques des différents sorts
static const float COEF_SPELL_SPEED(190.f);
static const float SPEED_SORT_1(20.f);
static const float SPEED_SORT_2(5.f);
static const float SPEED_SORT_3(1.f);
static const float POWER_SORT_1(10.f);
static const float POWER_SORT_2(20.f);
static const float POWER_SORT_3(45.f);
static const bool CAN_AFFECT_OWNER(false);

//	Enumération des états du programme au cours de sa vie (voir le diagramme de machine a état)
enum GAME_STATE {
	LOADING,
	MENU,
	PLAYING,
	QUITTING
};


static const float FRAME_DURATION(1000 / 60);

static const float INVOCATION_RECOVERYTIME(400);

#define MS_SINCE_BEGIN clock()

//	Structure qui contient le résultat de l'appel de la méthode receive
struct receiveResult {
	bool affectTarget;
	bool destroyBullet;
	bool returnBullet;
};

