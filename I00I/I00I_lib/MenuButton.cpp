#include "stdafx.h"
#include "MenuButton.h"
#include "constantes.h"
#include "Loader.h"

#define ISBETWEEN(x,a,b) ((x >= a) && (x <= b))

MenuButton::MenuButton(sf::Vector2f relativePosition, sf::String label, bool isSelected) :
relativePosition(relativePosition), isSelected(isSelected)
{
	auto& sin = Loader::Instance();
	sf::RectangleShape* selectionRectangle = new sf::RectangleShape;
	selectionRectangle->setFillColor(isSelected ? SELECT_BUTTON_COLOR : sf::Color::Transparent);

	sf::Sprite* ButtonRectangle = new sf::Sprite(*sin.getTexture(label));

	ButtonRectangle->setOrigin(BUTTON_ORIGINE);
	ButtonRectangle->setPosition(BUTTON_POSITION(relativePosition));

	selectionRectangle->setSize(SELECT_BUTTON_SIZE);
	selectionRectangle->setOrigin(SELECT_BUTTON_ORIGINE);
	selectionRectangle->setPosition(BUTTON_POSITION(relativePosition));

	sprites.push_back(std::unique_ptr<sf::RectangleShape>(selectionRectangle));
	sprites.push_back(std::unique_ptr<sf::Sprite>(ButtonRectangle));
}

void MenuButton::changeSelection() {
	if (isSelected) unselect(); else select();
}

bool MenuButton::getState() {
	return isSelected;
}

void MenuButton::select() {
	isSelected = true;
	((sf::RectangleShape*)sprites[0].get())->setFillColor(SELECT_BUTTON_COLOR);
}

void MenuButton::unselect() {
	isSelected = false;
	((sf::RectangleShape*)sprites[0].get())->setFillColor(sf::Color::Transparent);
}

bool MenuButton::isIn(sf::Vector2u position, sf::Vector2u windowSize) {
	sf::Vector2f absoluteButtonSize(windowSize.x * .25f, windowSize.y * .15f);
	sf::Vector2f absoluteButtonPosition(windowSize.x * relativePosition.x - absoluteButtonSize.x / 2.f,
		windowSize.y * relativePosition.y - absoluteButtonSize.y / 2.f);
	return ISBETWEEN(position.x, absoluteButtonPosition.x, absoluteButtonPosition.x + absoluteButtonSize.x)
		&& ISBETWEEN(position.y, absoluteButtonPosition.y, absoluteButtonPosition.y + absoluteButtonSize.y);
}
