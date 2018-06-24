#include "stdafx.h"
#include "Loader.h"


Loader* Loader::_instance = NULL;

Loader::Loader() {
	pugi::xml_parse_result result = doc.load_file(PATH_XML);
	assets.insert(std::make_pair("empty", new sf::Texture));
	sounds.insert(std::make_pair("empty", new sf::SoundBuffer));
	if (!result) {
		std::cout << "PugiXML n'arrive pas a ouvrir le fichier" << std::endl;
		std::cout << "Parse error: " << result.description() << ", character pos= " << result.offset;
	}
}

void Loader::loadFirst() {
	pugi::xml_node first = doc.document_element().child("first");
	for (auto& child : first.children()) {
		std::string textureName = (std::string)child.attribute("label").as_string();
		assets.insert(std::make_pair(textureName, new sf::Texture()));
		assets[textureName]->loadFromFile((std::string)child.attribute("path").as_string());
		assets[textureName]->setSmooth(true);
	}
}

void Loader::loadLast() {
	pugi::xml_node last = doc.document_element().child("last");
	for (auto& child : last.children()) {
		std::string textureName = (std::string)child.attribute("label").as_string();
		assets.insert(std::make_pair(textureName, new sf::Texture()));
		assets[textureName]->loadFromFile((std::string)child.attribute("path").as_string());
		assets[textureName]->setSmooth(true);
	}

	pugi::xml_node soundsList = doc.document_element().child("sounds");
	for (auto& child : soundsList.children()) {
		std::string textureName = (std::string)child.attribute("label").as_string();
		sounds.insert(std::make_pair(textureName, new sf::SoundBuffer()));
		sounds[textureName]->loadFromFile((std::string)child.attribute("path").as_string());
	}
}

sf::Texture* Loader::getTexture(std::string name) {
	if (assets.find(name) != assets.end()) {
		return assets[name].get();
	}
	return assets["empty"].get();
}

sf::SoundBuffer * Loader::getSound(std::string name) {
	if (sounds.find(name) != sounds.end()) {
		return sounds[name].get();
	}
	return sounds["empty"].get();
}

Loader & Loader::Instance() {
	// TODO: ins�rer une instruction return ici
	if (_instance == NULL) _instance = new Loader();
	return *_instance;
}

