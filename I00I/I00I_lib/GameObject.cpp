#include "stdafx.h"
#include "Game.h"
#include "GameObject.h"
#include "Spell.h"

b2Body * GameObject::getBody() {
	return body;
}

void GameObject::startContact() {}


receiveResult GameObject::receive(Spell * sort, sf::Vector2f spellPosition, int caster) {
	receiveResult result;
	result.affectTarget = false;
	result.destroyBullet = false;
	result.returnBullet = false;
	return result;
}

void GameObject::startContact(GameObject * objectToHit) {
	std::cout << "contact ignoré" << std::endl;
}

GameObject::~GameObject() {
	Game::getWorld()->DestroyBody(body);
}
