#pragma once

#define W_WIDTH (1000)
#define W_HEIGHT (1000)
#define W_TITLE "Hello World!"
#define PATH_BACKGROUND "..\\..\\Assets\\menu_background.jpg"

enum GAME_STATE {
	LOADING,
	MENU,
	PLAYING,
	QUITTING
};

#define GRAVITY_WORLD (b2Vec2(0.f, 1.f))

