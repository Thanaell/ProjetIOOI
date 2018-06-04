#include "stdafx.h"
#include "Loader.h"


Loader* Loader::_instance = NULL;

Loader::Loader() {
	pugi::xml_parse_result result = doc.load_file(PATH_XML);
	assets.insert(std::make_pair("empty", new sf::Texture));
	if (!result) {
		std::cout << "PugiXML n'arrive pas a ouvrir le fichier" << std::endl;
		std::cout << "Parse error: " << result.description() << ", character pos= " << result.offset;
	}
}

void Loader::loadFirst() {
	pugi::xml_node first = doc.document_element().child("first");
	for (auto& child : first.children()) {
		assets.insert(std::make_pair((std::string)child.attribute("label").as_string(), new sf::Texture()));
		assets[child.attribute("label").as_string()]->loadFromFile((std::string)child.attribute("path").as_string());
	}
}

void Loader::loadLast() {
	pugi::xml_node first = doc.document_element().child("last");
	for (auto& child : first.children()) {
		assets.insert(std::make_pair((std::string)child.attribute("label").as_string(), new sf::Texture()));
		assets[child.attribute("label").as_string()]->loadFromFile((std::string)child.attribute("path").as_string());
	}
}

sf::Texture* Loader::getTexture(std::string name) {
	if (assets.find(name) != assets.end()) {
		return assets[name].get();
	}
	return assets["empty"].get();
}

Loader & Loader::Instance() {
	// TODO: ins�rer une instruction return ici
	if (_instance == NULL) _instance = new Loader();
	return *_instance;
}

