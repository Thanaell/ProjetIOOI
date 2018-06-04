#pragma once
#include "stdafx.h"
#include "pugixml.hpp"
#include "constantes.h"


class Loader  {
private:
	pugi::xml_document doc;
	std::map<std::string, std::unique_ptr<sf::Texture>> assets;
	Loader();
	static Loader* _instance;
public:
	void loadFirst();
	void loadLast();
	sf::Texture* getTexture(std::string name);
	
	static Loader& Instance();
};

