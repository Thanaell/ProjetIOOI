#include "stdafx.h"
#include "MenuButton.h"

#define ISBETWEEN(x,a,b) ((x >= a) && (x <= b))

MenuButton::MenuButton(sf::Vector2u windowSize, sf::Vector2f relativePosition, sf::Vector2f relativeSize, sf::String label) :
relativePosition(relativePosition), relativeSize(relativeSize), isSelected(false)
{
	std::unique_ptr<sf::RectangleShape> selectionRectangle(new sf::RectangleShape);
	selectionRectangle->setFillColor(sf::Color::Transparent);
	sprites.push_back(std::move(selectionRectangle));
	std::unique_ptr<sf::RectangleShape> ButtonRectangle(new sf::RectangleShape);
	ButtonRectangle->setFillColor(sf::Color::Red);
	sprites.push_back(std::move(ButtonRectangle));
	std::unique_ptr<sf::Text> TextLabel(new sf::Text(label, sf::Font()));
	TextLabel->setFillColor(sf::Color::White);
	sprites.push_back(std::move(TextLabel));
	resizeSprites(windowSize);
}

void MenuButton::select() {
	isSelected = true;
	((sf::RectangleShape*)sprites[0].get())->setFillColor(sf::Color::Yellow);
}

void MenuButton::unselect() {
	isSelected = false;
	((sf::RectangleShape*)sprites[0].get())->setFillColor(sf::Color::Transparent);
}

bool MenuButton::isIn(sf::Vector2f position) {
	auto& positionButton = ((sf::RectangleShape*)sprites[0].get())->getPosition();
	auto& sizeButton = ((sf::RectangleShape*)sprites[0].get())->getSize();
	return ISBETWEEN(position.x, positionButton.x, positionButton.x + sizeButton.x)
		&& ISBETWEEN(position.y, positionButton.y, positionButton.y + sizeButton.y);
}

void MenuButton::resizeSprites(sf::Vector2u windowSize) {
}
