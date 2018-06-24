#pragma once
#include "stdafx.h"
#include "constantes.h"

// Classe parent de tous les �l�ments du jeu qui s'affichent a l'�cran (personnages, boutons, sortil�ges)
class Element {
protected:
	// Liste des sprites d'un �l�ment
	std::vector<std::shared_ptr<sf::Drawable>> sprites;
	/// un �l�ment peut avoir plusieurs sprite :
	/// par exemple un personnage a son sprite en jeu, mais aussi sa barre de vie dans un coin

	// Liste des sounds que joue l'�l�ment
	std::vector<std::unique_ptr<sf::Sound>> sounds;

public: 
	// Fonction qui affiche a l'�cran l'ensemble des sprite de la classe
	void draw(sf::RenderWindow & window) const;
	/// Pourra �venutellement etre override pour les personnages afin de n'afficher que certain sprite en fonction du contexte
};