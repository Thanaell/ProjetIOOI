#include "stdafx.h"
#include "Wall.h"
#include "Game.h"

Wall::Wall(b2Vec2 point1, b2Vec2 point2) :
	position(point1.x == point2.x ? point1.x : 0, point1.y == point2.y ? point1.y: 0)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	body = Game::getWorld()->CreateBody(&bodyDef);
	b2EdgeShape wall;
	wall.Set(point1, point2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &wall;
	body->CreateFixture(&fixtureDef);
}

b2Vec2 Wall::getPosition() {
	return position;
}

