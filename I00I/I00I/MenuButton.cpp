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
	/*std::unique_ptr<sf::Text> TextLabel(new sf::Text(label, sf::Font()));
	TextLabel->setFillColor(sf::Color::White);
	sprites.push_back(std::move(TextLabel));*/
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
	sf::Vector2f absoluteButtonSize(windowSize.x * relativeSize.x, windowSize.y * relativeSize.y);
	sf::Vector2f absoluteButtonPosition(windowSize.x * relativePosition.x - absoluteButtonSize.x / 2.f,
										windowSize.y * relativePosition.y - absoluteButtonSize.y / 2.f);
	((sf::RectangleShape*)sprites[1].get())->setSize(absoluteButtonSize);
	((sf::RectangleShape*)sprites[1].get())->setPosition(absoluteButtonPosition);
#ifdef DEBUG_LOG
	std::cout << "position button : " << absoluteButtonPosition.x << " ; " << absoluteButtonPosition.y;
	std::cout << " size button : " << absoluteButtonSize.x << " ; " << absoluteButtonSize.y;
	std::cout << " windows size : " << windowSize.x << " ; " << windowSize.y << std::endl;
#endif
	((sf::RectangleShape*)sprites[0].get())->setSize(sf::Vector2f(absoluteButtonSize.x * 1.05f, absoluteButtonSize.y * 1.05f));
	((sf::RectangleShape*)sprites[0].get())->setPosition(sf::Vector2f(absoluteButtonPosition.x * .975f, absoluteButtonPosition.y * .975f));
/*
	((sf::Text*)sprites[2].get())->setCharacterSize((unsigned int)(absoluteButtonSize.y * .70));
	((sf::Text*)sprites[2].get())->setPosition(sf::Vector2f(absoluteButtonPosition.x * 1.1, absoluteButtonPosition.y * 1.1));*/
}
