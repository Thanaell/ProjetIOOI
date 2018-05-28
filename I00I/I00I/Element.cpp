#include "stdafx.h"
#include "Element.h"

void Element::draw(sf::RenderWindow window) const {
	for (auto &sprite : sprites)	window.draw(*sprite);
}
