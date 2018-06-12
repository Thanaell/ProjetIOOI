#pragma once
#include "stdafx.h"
#include "Element.h"

// Bouton du menu
class MenuButton : public Element {
	// Position du centre du bouton sur la fenetre, entre 0 et 1. l'origine est en haut a gauche
	sf::Vector2f relativePosition;
	// Permet de s'avoir si le bouton est sélectionné (pratique quand on joue a la manette)
	bool isSelected;
	void select();
	void unselect();

public:
	MenuButton(sf::Vector2f relativePosition, sf::String label = "", bool isSelected = false);
	void changeSelection();
	bool getState();
	bool isIn(sf::Vector2u position, sf::Vector2u windowSize);
};