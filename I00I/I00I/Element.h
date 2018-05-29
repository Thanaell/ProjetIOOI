#pragma once
#include "stdafx.h"

class Element {
protected:
	std::vector<std::unique_ptr<sf::Drawable>> sprites;
public: 
	void draw(sf::RenderWindow & window) const;
};