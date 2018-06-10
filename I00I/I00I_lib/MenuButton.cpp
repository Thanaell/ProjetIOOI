#include "stdafx.h"
#include "MenuButton.h"
#include "constantes.h"
#include "Loader.h"

#define ISBETWEEN(x,a,b) ((x >= a) && (x <= b))

MenuButton::MenuButton(sf::Vector2f relativePosition, sf::String label) :
relativePosition(relativePosition), isSelected(false)
{
	auto& sin = Loader::Instance();
	sf::RectangleShape* selectionRectangle = new sf::RectangleShape;
	selectionRectangle->setFillColor(sf::Color::Transparent);
	sprites.push_back(std::unique_ptr<sf::RectangleShape>(selectionRectangle));

	sf::Sprite* ButtonRectangle = new sf::Sprite(*sin.getTexture(label));

	ButtonRectangle->setOrigin(sf::Vector2f(160.f, 54.f));
	ButtonRectangle->setPosition(sf::Vector2f(relativePosition.x * W_WIDTH, relativePosition.y * W_HEIGHT));

	selectionRectangle->setSize(sf::Vector2f(330.f, 114.f));
	selectionRectangle->setOrigin(sf::Vector2f(165.f, 57.f));
	selectionRectangle->setPosition(sf::Vector2f(relativePosition.x * W_WIDTH, relativePosition.y * W_HEIGHT));


	sprites.push_back(std::unique_ptr<sf::Sprite>(ButtonRectangle));
}

void MenuButton::select() {
	isSelected = true;
	((sf::RectangleShape*)sprites[0].get())->setFillColor(sf::Color::Yellow);
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
