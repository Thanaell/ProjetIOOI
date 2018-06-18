#include "stdafx.h"
#include "PlayingElement.h"
#include "Game.h"

bool PlayingElement::updateMovingSprite(sf::Sprite* sprite) {
	auto b2position = body->GetPosition();
	sf::Vector2f position(b2position.x * RATIO_WINDOWS_B2D, W_HEIGHT - b2position.y * RATIO_WINDOWS_B2D);
	if (position.x < 0 || position.x > W_WIDTH || position.y < 0 || position.y > W_HEIGHT) {
		return false;
	}
	sprite->setPosition(position);

	if ((!isFacingRight && sprite->getScale().x > 0)
		|| (isFacingRight && sprite->getScale().x < 0)) {
		sprite->scale(sf::Vector2f(-1.f, 1.f));
	}
	return true;
}

b2Body* PlayingElement::getBody() {
	return body;
}

PlayingElement::~PlayingElement() {
	Game::getWorld()->DestroyBody(body);
}

