#pragma once
#include "stdafx.h"
#include "Element.h"

class MenuButton : public Element {
	sf::Vector2f relativePosition;
	sf::Vector2f relativeSize;
	bool isSelected;

public:
	MenuButton(sf::Vector2u windowSize, sf::Vector2f relativePosition, sf::Vector2f relativeSize, sf::String label = "");
	void select();
	void unselect();
	bool isIn(sf::Vector2f position);
	void resizeSprites(sf::Vector2u windowSize) override;
};