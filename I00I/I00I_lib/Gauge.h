#pragma once

#include "stdafx.h"
#include "constantes.h"

//	Représente une jauge d'un personnage (jauge de vie, de bouclier ou de super)
class Gauge{
	float value;
	float maxValue;
	std::vector<std::unique_ptr<sf::Drawable>> sprites;
	bool horizontal;
	void updateSprites();

public:
	// Construit une nouvelle jauge
	Gauge(float maxValue, sf::Vector2f position, sf::Vector2f size, sf::Color color, float startValue = 0.f , bool horizontal = true);
	void add(float value);
	void remove(float value);
	void setValue(float value);
	bool isFull();
	bool isEmpty();
	float getValue();
};