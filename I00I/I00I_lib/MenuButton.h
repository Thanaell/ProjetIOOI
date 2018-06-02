#pragma once
#include "stdafx.h"
#include "Element.h"

// Bouton du menu
class MenuButton : public Element {
	// Position du centre du bouton sur la fenetre, entre 0 et 1. l'origine est en haut a gauche
	sf::Vector2f relativePosition;
	// Taille relative du bouton (sans inclure la surbrillance) par rapport a la taille de la fenetre. 1 = taille de la fenetre
	sf::Vector2f relativeSize;
	// Permet de s'avoir si le bouton est sélectionné (pratique quand on joue a la manette)
	bool isSelected;

public:
	MenuButton(sf::Vector2f relativePosition, sf::Vector2f relativeSize, sf::String label = "");
	void select();
	void unselect();
	bool isIn(sf::Vector2f position, sf::Vector2u windowSize);
};