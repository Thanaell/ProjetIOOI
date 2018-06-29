#include "stdafx.h"
#include "PlayingElement.h"
#include "Game.h"

bool PlayingElement::updateMovingSprite(sf::Sprite* sprite) {
	auto b2position = body->GetPosition();
	sf::Vector2f position(b2position.x * RATIO_WINDOWS_B2D, W_HEIGHT - b2position.y * RATIO_WINDOWS_B2D);
	if (position.x < -50.f || position.x > W_WIDTH + 50.f || position.y < -50.f || position.y > W_HEIGHT + 50.f) {
		return false;
	}
	sprite->setPosition(position);

	if ((!isFacingRight && sprite->getScale().x > 0)
		|| (isFacingRight && sprite->getScale().x < 0)) {
		sprite->scale(sf::Vector2f(-1.f, 1.f));
	}
	updateSizeSprite(sprite);
	sprite->setRotation(body->GetAngle());
	return true;
}

//	à implémenter
void PlayingElement::updateSizeSprite(sf::Sprite * sprite) {
	b2Vec2* bodySize = nullptr;
	float radius;
	auto shape = body->GetFixtureList();
	switch (shape->GetType()) {
	case b2Shape::Type::e_circle:
		radius = ((b2CircleShape*)shape->GetShape())->m_radius;
		bodySize = new b2Vec2(2 * radius, 2 * radius);
		break;
	case b2Shape::Type::e_edge: break;
	case b2Shape::Type::e_polygon:
		bodySize = new b2Vec2(((b2PolygonShape*)shape->GetShape())->GetVertex(0).Length() * 1.44,
							  ((b2PolygonShape*)shape->GetShape())->GetVertex(1).Length() * 1.44);
		break;
	case b2Shape::Type::e_chain: break;
	case b2Shape::Type::e_typeCount: break;
	}
	if (bodySize != nullptr) {
		sf::Vector2f ratioSizeWorld(bodySize->x / Game::getWorldSize().x, bodySize->y / Game::getWorldSize().y);
		sf::Vector2f sizeSprite(ratioSizeWorld.x * W_WIDTH, ratioSizeWorld.y * W_HEIGHT);

		auto textureSize = sprite->getTexture()->getSize();
		sprite->setScale((isFacingRight ? 1 : -1) * sizeSprite.x / textureSize.x, sizeSprite.y / textureSize.y);
	}
}

PlayingElement::PlayingElement() : toDestroy(false) {}

PlayingElement * PlayingElement::action() {
	return nullptr;
}

float PlayingElement::getHealth() {
	return 1000.f;
}

int PlayingElement::getNumber() {
	return 0;
}

bool PlayingElement::isToDestroy() {
	return toDestroy;
}

