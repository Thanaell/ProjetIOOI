#include "stdafx.h"
#include "Gauge.h"

Gauge::Gauge(sf::Color color, sf::Vector2f position, sf::Vector2f size, ORIGINE origine, float maxValue, float startValue, bool horizontal):
	maxValue(maxValue),
	value(startValue),
	horizontal(horizontal) {
	auto& sin = Loader::Instance();

	sf::RectangleShape* barreVie = new sf::RectangleShape(size);
	barreVie->setOrigin(calculateOrigine(origine, size.x, size.y));
	barreVie->setRotation(calculateRotation(origine));
	barreVie->setPosition(position);
	barreVie->setFillColor(color);
	sprites.push_back(barreVie);

	sf::Sprite* interfacePlayer = new sf::Sprite(*sin.getTexture("interfacePlayer"));
	interfacePlayer->setOrigin(calculateOrigine(origine, INTERFACE_PLAYER_SIZE_X, INTERFACE_PLAYER_SIZE_Y));
	interfacePlayer->setRotation(calculateRotation(origine));
	interfacePlayer->setScale(calculateScale(size));
	interfacePlayer->setPosition(position);
	interfacePlayer->setColor(sf::Color(255, 255, 255, 195));
	sprites.push_back(interfacePlayer);
}

void Gauge::add(float added) { 
	value = std::min(value + added, maxValue); 
	updateSprites(); 
}

void Gauge::remove(float removed) { 
	value = std::max(value - removed, 0.f);
	updateSprites(); 
}

void Gauge::setValue(float newValue) {
	value = newValue >= 0 && newValue <= maxValue ? newValue : value; 
	updateSprites(); 
}

void Gauge::setMaxValue(float newMaxValue) {
	maxValue = std::max(newMaxValue, 0.f);
	value = std::min(value, maxValue);
	updateSprites();
}

bool Gauge::isFull() { return value == maxValue; }

bool Gauge::isEmpty() { return value == 0; }

float Gauge::getValue() { return value; }

float Gauge::getRatio() {
	return value / maxValue;
}

const std::vector<sf::Drawable*>& Gauge::getSprite() { return sprites; }


void Gauge::updateSprites() {
	((sf::RectangleShape*)sprites[0])->setScale(sf::Vector2f(value / maxValue > 0.f ? value / maxValue : 0, 1.f));
}

sf::Vector2f Gauge::calculateOrigine(ORIGINE origine, float sizeX, float sizeY) {
	switch (origine) {
	case TOPLEFT: return sf::Vector2f(0.f, 0.f);
	case TOPRIGHT: return sf::Vector2f(sizeX, 0.f);
	case BOTTOMLEFT: return sf::Vector2f(0.f, sizeY);
	case BOTTOMRIGHT: return sf::Vector2f(sizeX, sizeY);
	case CENTER: return sf::Vector2f(sizeX / 2, sizeY / 2);
	default: return sf::Vector2f(0.f, 0.f);
	}
}

sf::Vector2f Gauge::calculateScale(sf::Vector2f size) {
	return sf::Vector2f(size.x / INTERFACE_PLAYER_SIZE_X, size.y / INTERFACE_PLAYER_SIZE_Y);
}

float Gauge::calculateRotation(ORIGINE origine) {
	if(horizontal) return 0.0f;
	switch (origine) {
	case TOPLEFT: return -90.f;
	case TOPRIGHT: return 90.f;
	case BOTTOMLEFT: return 90.f;
	case BOTTOMRIGHT: return -90.f;
	case CENTER: return -90.f;
	default: return 0.f;
	}
}


