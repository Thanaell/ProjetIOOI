#pragma once
#include "stdafx.h"
#include "constantes.h"

// Classe parent de tous les éléments du jeu qui s'affichent a l'écran (personnages, boutons, sortilèges)
class Element {
protected:
	// Liste des sprites d'un élément
	std::vector<std::shared_ptr<sf::Drawable>> sprites;
	/// un élément peut avoir plusieurs sprite :
	/// par exemple un personnage a son sprite en jeu, mais aussi sa barre de vie dans un coin

	// Liste des sounds que joue l'élément
	std::vector<std::unique_ptr<sf::Sound>> sounds;

public: 
	// Fonction qui affiche a l'écran l'ensemble des sprite de la classe
	void draw(sf::RenderWindow & window) const;
	/// Pourra évenutellement etre override pour les personnages afin de n'afficher que certain sprite en fonction du contexte
};