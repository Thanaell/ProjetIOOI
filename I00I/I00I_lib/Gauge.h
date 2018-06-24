#pragma once

#include "stdafx.h"
#include "constantes.h"
#include "Loader.h"

//	Représente une jauge d'un personnage (jauge de vie, de bouclier ou de super)
class Gauge{
	float value;
	float maxValue;
	std::vector<sf::Drawable*> sprites;
	bool horizontal;
	void updateSprites();
	sf::Vector2f calculateOrigine(ORIGINE origine, float sizeX, float sizeY);
	sf::Vector2f calculateScale(sf::Vector2f size);
	float calculateRotation(ORIGINE origine);

public:
	// Construit une nouvelle jauge
	Gauge(sf::Color color, sf::Vector2f position, sf::Vector2f size, ORIGINE origine = TOPLEFT, float maxValue = 0.f, float startValue = 0.f , bool horizontal = true);
	void add(float added);
	void remove(float removed);
	void setValue(float newValue);
	void setMaxValue(float newMaxValue);
	bool isFull();
	bool isEmpty();
	float getValue();
	float getRatio();
	const std::vector<sf::Drawable*> & getSprite();
};