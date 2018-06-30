#include "stdafx.h"
#include "Element.h"

sf::Sprite * Element::loadSprite(std::string textureName) {
	auto& sin = Loader::Instance();
	sf::Sprite* sprite = new sf::Sprite(*sin.getTexture(textureName));
	auto textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.x / 2);
	return sprite;
}

void Element::draw(sf::RenderWindow & window) const {
	for (auto &sprite : sprites)
		window.draw(*sprite);
}
